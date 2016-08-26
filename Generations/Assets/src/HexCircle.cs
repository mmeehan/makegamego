using UnityEngine;

namespace Generations
{
    [RequireComponent(typeof(HexGridMesh))]
    public class HexCircle : MonoBehaviour
    {
        [SerializeField]
        private float edgeLength = 1.0f;

        [SerializeField]
        private float space = 0.05f;

        [SerializeField]
        private int hexCount = 7;
        
        public void Awake()
        {
            HexCorners centerHex = HexCorners.Create(Vector3.zero, Vector3.up, this.edgeLength);
            HexTile[] hexes = new HexTile[this.hexCount];
            
            float centerToCenterDistance = 2 * this.edgeLength * Mathf.Cos(Mathf.Deg2Rad * 30f);

            for (int hexIdx = 0; hexIdx < this.hexCount; hexIdx++)
            {
                HexCorners hex;
                if (hexIdx == 0)
                {
                    hex = centerHex;
                }
                else
                {
                    Vector3 direction = centerHex.GetNeighborDirection((hexIdx - 1) % 6);
                    Vector3 center = direction * (centerToCenterDistance + this.space);
                    hex = HexCorners.Create(center, Vector3.up, this.edgeLength);
                }

                hexes[hexIdx] = new HexTile(hex);
            }

            this.GetComponent<HexGridMesh>().GenerateMesh(hexes);
        }
    }
}