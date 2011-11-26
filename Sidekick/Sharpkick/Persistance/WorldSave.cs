using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sharpkick
{
    class WorldSave
    {
        /// <summary>
        /// The frequency at which the world should save, in minutes
        /// </summary>
        public static TimeSpan SaveFreq = TimeSpan.FromMinutes(10.0);

        public static void Configure()
        {
            EventSink.OnPulse += new OnPulseEventHandler(EventSink_OnPulse);
        }

        static void EventSink_OnPulse()
        {
            if (Server.TimeManager.PulseNum % ((int)SaveFreq.TotalSeconds * 4) == 0) Server.SaveWorld();
        }
    }
}
