using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ArtificialIntelligenceUI;

namespace StartForm
{
    public interface Observable
    {
        void RegisterObserver(ArtificialIntelligences anAI);
        void NotifyObserver();
        void RemoveObserver(ArtificialIntelligences anAI);
    }
}
