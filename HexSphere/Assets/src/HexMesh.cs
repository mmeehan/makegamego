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

            this.vertices = new Vector3[6];
            this.triangles = new int[12];
            this.texCoords = new Vector2[6];

            Vector3 offset = new Vector3(0f, 0f, this.edgeLength);

            Quaternion rotation = Quaternion.AngleAxis(60f, Vector3.up);
            for (int vertexIdx = 0; vertexIdx < this.vertices.Length; vertexIdx++)
            {
                this.vertices[vertexIdx] = offset;
                offset = rotation * offset;

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