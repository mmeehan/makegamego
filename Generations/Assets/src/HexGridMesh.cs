using UnityEngine;

namespace Generations
{
    [RequireComponent(typeof(MeshRenderer))]
    [RequireComponent(typeof(MeshFilter))]
    public class HexGridMesh : MonoBehaviour
    {
        private MeshFilter meshFilter;
        private Vector3[] vertices;
        private int[] triangles;
        private Vector2[] texCoords;
        private Vector3[] hexCenters;
        
        public void GenerateMesh(HexTile[] hexTiles)
        {
            // NOTE TO SELF: It would be super cool if the sphere flattened out as you zoomed in!


            Mesh mesh = new Mesh();

            this.meshFilter = this.GetComponent<MeshFilter>();
            this.meshFilter.mesh = mesh;
            
            int hexCount = hexTiles.Length;

            this.hexCenters = new Vector3[hexCount];
            this.vertices = new Vector3[6 * hexCount];
            this.triangles = new int[12 * hexCount];
            this.texCoords = new Vector2[6 * hexCount];
            
            for (int hexIdx = 0; hexIdx < hexTiles.Length; hexIdx++)
            {
                HexTile hex = hexTiles[hexIdx];
                this.hexCenters[hexIdx] = hex.corners.center;

                int vertexHexOffset = hexIdx * 6;
                int triangleHexOffset = hexIdx * 12;
                
                for (int vertexIdx = 0; vertexIdx < hex.corners.Length; vertexIdx++)
                {
                    this.vertices[vertexHexOffset + vertexIdx] = hex.corners[vertexIdx];

                    // TODO: assign sane texture coordinates.
                    this.texCoords[vertexHexOffset + vertexIdx] = Vector2.zero;
                }

                for (int triangleIdx = 0; triangleIdx < 4; triangleIdx++)
                {
                    this.triangles[triangleHexOffset + triangleIdx * 3] = vertexHexOffset + 0;
                    this.triangles[triangleHexOffset + triangleIdx * 3 + 1] = vertexHexOffset + triangleIdx + 1;
                    this.triangles[triangleHexOffset + triangleIdx * 3 + 2] = vertexHexOffset + triangleIdx + 2;
                }
            }

            mesh.vertices = this.vertices;
            mesh.triangles = this.triangles;
            mesh.uv = this.texCoords;
        }

        public void OnDrawGizmosSelected()
        {
            if (this.triangles != null && this.vertices != null)
            {
                for (int i = 0; i < this.triangles.Length; i += 3)
                {
                    Vector3 first = this.vertices[this.triangles[i]];
                    Vector3 second = this.vertices[this.triangles[i + 1]];
                    Vector3 third = this.vertices[this.triangles[i + 2]];

                    Gizmos.color = Color.red;
                    Gizmos.DrawLine(first, second);
                    Gizmos.DrawLine(second, third);
                    Gizmos.DrawLine(third, first);
                }
            }

            if (this.hexCenters != null)
            {
                for (int i = 0; i < this.hexCenters.Length; i++)
                {
#if UNITY_EDITOR
                    UnityEditor.Handles.Label(this.hexCenters[i], i.ToString());
#endif
                }
            }
        }
    }
}