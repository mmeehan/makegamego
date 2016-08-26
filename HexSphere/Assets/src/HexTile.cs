using UnityEngine;
using System;

namespace HexSphere
{
    public struct HexTile
    {
        public readonly HexCorners corners;

        public HexTile(HexCorners _corners)
        {
            this.corners = _corners;
        }
    }
}