using UnityEngine;

namespace HexSphere
{
    [RequireComponent(typeof(MeshRenderer))]
    [RequireComponent(typeof(MeshFilter))]
    public class HexMesh : MonoBehaviour
    {
        [SerializeField]
        private float edgeLength = 1.0f;
        
        private MeshFilter meshFilter;
        private Vector3[] vertices;
        private int[] triangles;
        private Vector2[] texCoords;

        public void Awake()
        {
            Mesh mesh = new Mesh();

            this.meshFilter = this.GetComponent<MeshFilter>();
            this.meshFilter.mesh = mesh;

            HexCorners hex = HexCorners.Create(Vector3.zero, Vector3.up, this.edgeLength);

            this.vertices = new Vector3[hex.Length];
            this.triangles = new int[12];
            this.texCoords = new Vector2[6];
            
            for (int vertexIdx = 0; vertexIdx < this.vertices.Length; vertexIdx++)
            {
                this.vertices[vertexIdx] = hex[vertexIdx];

                // TODO: assign sane texture coordinates.
                this.texCoords[vertexIdx] = Vector2.zero;
            }

            for (int triangleIdx = 0; triangleIdx < 4; triangleIdx++)
            {
                this.triangles[triangleIdx * 3] = 0;
                this.triangles[triangleIdx * 3 + 1] = triangleIdx + 1;
                this.triangles[triangleIdx * 3 + 2] = triangleIdx + 2;
            }

            mesh.vertices = this.vertices;
            mesh.triangles = this.triangles;
            mesh.uv = this.texCoords;
        }
    }
}