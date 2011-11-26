using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sharpkick
{
    class MyServerConfig
    {
        public const ushort MaxNonNormalMobilesSpawned=15000;

        public static bool ResourceDebug { get { return true; } }
        public static bool ResourceGrowthFastMode { get { return false; } }

    }
}
