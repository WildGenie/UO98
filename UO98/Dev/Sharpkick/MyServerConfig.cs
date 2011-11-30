using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sharpkick
{
    static class MyServerConfig
    {
        #region Spawner

        public const ushort MaxNonNormalMobilesSpawned=15000;

        public static bool ResourceDebug { get { return true; } }
        public static bool ResourceGrowthFastMode { get { return false; } }

        #endregion

        #region Saves

        /// <summary>The frequency at which the world should save</summary>
        public static TimeSpan SaveFreq = TimeSpan.FromMinutes(10.0);
        public static bool AutoSaveEnabled { get { return false; } }

        #endregion

        #region Decoration

        public static bool DecorationEnabled { get { return false; } }

        #endregion

    }
}
