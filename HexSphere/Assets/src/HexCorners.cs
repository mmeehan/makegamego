using UnityEngine;
using System;

namespace HexSphere
{
    public struct HexCorners
    {
        public readonly Vector3 center;
        public readonly Vector3 north;
        public readonly Vector3 northEast;
        public readonly Vector3 southEast;
        public readonly Vector3 south;
        public readonly Vector3 southWest;
        public readonly Vector3 northWest;

        public int Length { get { return 6; } }

        public Vector3 this[int index]
        {
            get
            {
                switch (index)
                {
                    case 0:
                        return this.north;
                    case 1:
                        return this.northEast;
                    case 2:
                        return this.southEast;
                    case 3:
                        return this.south;
                    case 4:
                        return this.southWest;
                    case 5:
                        return this.northWest;
                    default:
                        throw new IndexOutOfRangeException();
                }
            }
        }

        private HexCorners(Vector3 _center, Vector3[] vertices)
        {
            if (vertices.Length != 6)
            {
                throw new ArgumentOutOfRangeException();
            }

            this.center = _center;
            this.north = vertices[0];
            this.northEast = vertices[1];
            this.southEast = vertices[2];
            this.south = vertices[3];
            this.southWest = vertices[4];
            this.northWest = vertices[5];
        }

        public static HexCorners Create(Vector3 center, Vector3 normal, float radiusAtCenterOfEdge)
        {
            Vector3[] vertices = new Vector3[6];

            Vector3 localOffset = new Vector3(0f, 0f, radiusAtCenterOfEdge);
            Quaternion rotationPerStep = Quaternion.AngleAxis(60f, Vector3.up);
            Quaternion normalRotation = Quaternion.FromToRotation(Vector3.up, normal);

            for (int vertexIdx = 0; vertexIdx < vertices.Length; vertexIdx++)
            {
                Vector3 rotatedOffset = normalRotation * localOffset;
                vertices[vertexIdx] = center + rotatedOffset;
                localOffset = rotationPerStep * localOffset;
            }

            return new HexCorners(center, vertices);
        }

        // TODO: move this out and consider caching it.
        public Vector3 GetNeighborDirection(int faceIndex)
        {
            if (faceIndex < 0 || faceIndex >= this.Length)
            {
                throw new ArgumentOutOfRangeException();
            }

            Vector3 centerOfFace = (this[faceIndex] + this[(faceIndex + 1) % Length]) * 0.5f;
            return (centerOfFace - this.center).normalized;
        }
    }
}