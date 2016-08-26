using UnityEngine;
using System;

namespace HexSphere
{
    public struct HexVertices
    {
        public readonly Vector3 Center;
        public readonly Vector3 North;
        public readonly Vector3 NorthEast;
        public readonly Vector3 SouthEast;
        public readonly Vector3 South;
        public readonly Vector3 SouthWest;
        public readonly Vector3 NorthWest;

        public int Length { get { return 6; } }

        public Vector3 this[int index]
        {
            get
            {
                switch (index)
                {
                    case 0:
                        return this.North;
                    case 1:
                        return this.NorthEast;
                    case 2:
                        return this.SouthEast;
                    case 3:
                        return this.South;
                    case 4:
                        return this.SouthWest;
                    case 5:
                        return this.NorthWest;
                    default:
                        throw new IndexOutOfRangeException();
                }
            }
        }

        private HexVertices(Vector3 center, Vector3[] vertices)
        {
            if (vertices.Length != 6)
            {
                throw new ArgumentOutOfRangeException();
            }

            this.Center = center;
            this.North = vertices[0];
            this.NorthEast = vertices[1];
            this.SouthEast = vertices[2];
            this.South = vertices[3];
            this.SouthWest = vertices[4];
            this.NorthWest = vertices[5];
        }

        public static HexVertices Create(Vector3 center, float edgeLength)
        {
            Vector3[] vertices = new Vector3[6];
            Vector3 offset = new Vector3(0f, 0f, edgeLength);

            Quaternion rotation = Quaternion.AngleAxis(60f, Vector3.up);
            for (int vertexIdx = 0; vertexIdx < vertices.Length; vertexIdx++)
            {
                vertices[vertexIdx] = center + offset;
                offset = rotation * offset;
            }

            return new HexVertices(center, vertices);
        }

        public Vector3 GetNeighborDirection(int faceIndex)
        {
            if (faceIndex < 0 || faceIndex >= this.Length)
            {
                throw new ArgumentOutOfRangeException();
            }

            Vector3 centerOfFace = (this[faceIndex] + this[(faceIndex + 1) % Length]) * 0.5f;
            return (centerOfFace - this.Center).normalized;
        }
    }
}