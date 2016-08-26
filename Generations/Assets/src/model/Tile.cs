using UnityEngine;

namespace Generations.Model
{
    public struct Tile
    {
        public readonly TileSpherePosition position;
        
        private Tile(TileSpherePosition _position)
        {
            this.position = _position;
        }
    }
}