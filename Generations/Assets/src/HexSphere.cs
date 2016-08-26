using UnityEngine;

namespace Generations
{
    [RequireComponent(typeof(HexGridMesh))]
    public class HexSphere : MonoBehaviour
    {
        [SerializeField]
        private float edgeLength = 1.0f;

        [SerializeField]
        private float space = 0.05f;

        //[SerializeField]
        //private int layersPerHemisphere = 1;

        public void Awake()
        {
            this.RebuildGrid();
        }

        public void RebuildGrid()
        {
            float sphereRadius = this.edgeLength * 3; // TODO: compute this.
            
            HexCorners top = HexCorners.Create(Vector3.up * sphereRadius, Vector3.up, this.edgeLength);
            HexCorners bottom = HexCorners.Create(Vector3.down * sphereRadius, Vector3.down, this.edgeLength);
            
            // for now we know it's 8 tiles around 
            HexTile[] hexes = new HexTile[1 + 6 + 8 + 6 + 1];

            float anglePerLayer = 360f / 5;
            
            hexes[0] = new HexTile(top);

            int tileIdx = 1;
            for (int i = 0; i < 6; i++)
            {
                float anglePerTile = 360f / 6;
                Vector3 center = Quaternion.Euler(0f, anglePerTile * i, 180f - (anglePerLayer * 1f)) * Vector3.right * sphereRadius;
                hexes[tileIdx] = new HexTile(HexCorners.Create(center, center.normalized, this.edgeLength));
                tileIdx++;
            }

            for (int i = 0; i < 8; i++)
            {
                float anglePerTile = 360f / 8;
                Vector3 center = Quaternion.Euler(0f, anglePerTile * i, 0f) * Vector3.right * sphereRadius;
                hexes[tileIdx] = new HexTile(HexCorners.Create(center, center.normalized, this.edgeLength));
                tileIdx++;
            }

            for (int i = 0; i < 6; i++)
            {
                float anglePerTile = 360f / 6;
                Vector3 center = Quaternion.Euler(0f, anglePerTile * i, 180f - (anglePerLayer * 4f)) * Vector3.right * sphereRadius;
                hexes[tileIdx] = new HexTile(HexCorners.Create(center, center.normalized, this.edgeLength));
                tileIdx++;
            }

            hexes[tileIdx] = new HexTile(bottom);
            
            this.GetComponent<HexGridMesh>().GenerateMesh(hexes);
        }
    }
}