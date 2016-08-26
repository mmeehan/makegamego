using UnityEngine;

namespace HexSphere
{
    [RequireComponent(typeof(MeshRenderer))]
    [RequireComponent(typeof(MeshFilter))]
    public class HexGridMesh : MonoBehaviour
    {
        private MeshFilter meshFilter;
        private Vector3[] vertices;
        private int[] triangles;
        private Vector2[] texCoords;
        
        public void GenerateMesh(HexTile[] hexTiles)
        {
            Mesh mesh = new Mesh();

            this.meshFilter = this.GetComponent<MeshFilter>();
            this.meshFilter.mesh = mesh;
            
            int hexCount = hexTiles.Length;

            this.vertices = new Vector3[6 * hexCount];
            this.triangles = new int[12 * hexCount];
            this.texCoords = new Vector2[6 * hexCount];
            
            for (int hexIdx = 0; hexIdx < hexTiles.Length; hexIdx++)
            {
                int vertexHexOffset = hexIdx * 6;
                int triangleHexOffset = hexIdx * 12;

                HexTile hex = hexTiles[hexIdx];
                
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
    }
}