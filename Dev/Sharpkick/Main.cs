using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using Sharpkick.Network;

namespace Sharpkick
{
    class Main
    {
        /// <summary>
        /// Indicates that we have run our initialization routines
        /// </summary>
        public static bool Initialized {get;private set;}

        /// <summary>
        /// Called once, on first pulse from server. Set everything up here.
        /// </summary>
        public static void Initialize()
        {
            if(!Initialized)
            {
                // Call all class configuration routines.
                WorldSave.Configure();
                Accounting.Configure();
                PacketVersions.Configure();

                Initialized=true;

                Sharpkick.WorldBuilding.Builder.Configure();

                Console.WriteLine("Sharpkick Initialized.");
            }
        }
    }
}
