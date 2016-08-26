using UnityEngine;
using System;

namespace Generations
{
    public struct HexSphereCoordinate
    {
        public int Layer; // the hex's layer / vertical position. Kinda like latitude.
        public int Offset; // the hex's position in the sequence of hexes around the circumference of a layer. Kinda like longitude.
    }
}