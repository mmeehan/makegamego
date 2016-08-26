namespace Generations.Model
{
    public struct TileSpherePosition
    {
        private readonly int layer;
        private readonly int offsetWithinLayer;

        public TileSpherePosition(int _layer, int _offset)
        {
            this.layer = _layer;
            this.offsetWithinLayer = _offset;
        }
    }
}