namespace Generations.Model
{
    public struct TileSphere
    {
        private readonly Tile[][] layers;

        public Tile this[int layer, int offset]
        {
            get
            {
                throw new System.NotImplementedException();
            }
        }

        private TileSphere(HexTile[][] _layers)
        {
            throw new System.NotImplementedException();
        }

        public static TileSphere Create(int layers)
        {
            throw new System.NotImplementedException();
        }
    }
}