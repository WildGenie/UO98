using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sharpkick
{
    static partial class Server
    {
        unsafe public static void SendInfoWindowOrDoPlayerShadow(HelpInfoArgs arg)
        {
            Core.SendInfoWindowOrDoPlayerShadow(&arg);
        }
    }
}
