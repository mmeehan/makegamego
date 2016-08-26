using UnityEngine;

namespace HexSphere
{
    [RequireComponent(typeof(MeshRenderer))]
    [RequireComponent(typeof(MeshFilter))]
    public class HexGridMesh : MonoBehaviour
    {
        [SerializeField]
        private float edgeLength = 1.0f;

        [SerializeField]
        private float space = 0.05f;

        [SerializeField]
        private int hexCount = 7;

        private MeshFilter meshFilter;
        private Vector3[] vertices;
        private int[] triangles;
        private Vector2[] texCoords;

        public void Awake()
        {
            Mesh mesh = new Mesh();

            this.meshFilter = this.GetComponent<MeshFilter>();
            this.meshFilter.mesh = mesh;

            HexVertices centerHex = HexVertices.Create(Vector3.zero, this.edgeLength);

            this.vertices = new Vector3[centerHex.Length * this.hexCount];
            this.triangles = new int[12 * this.hexCount];
            this.texCoords = new Vector2[6 * this.hexCount];

            float centerToCenterDistance = 2 * this.edgeLength * Mathf.Cos(Mathf.Deg2Rad * 30f);

            for (int hexIdx = 0; hexIdx < this.hexCount; hexIdx++)
            {
                int vertexHexOffset = hexIdx * 6;
                int triangleHexOffset = hexIdx * 12;

                HexVertices hex;
                if (hexIdx == 0)
                {
                    hex = centerHex;
                }
                else
                {
                    Vector3 direction = centerHex.GetNeighborDirection((hexIdx - 1) % 6);
                    hex = HexVertices.Create(direction * (centerToCenterDistance + this.space), this.edgeLength);
                }

                for (int vertexIdx = 0; vertexIdx < hex.Length; vertexIdx++)
                {
                    this.vertices[vertexHexOffset + vertexIdx] = hex[vertexIdx];

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