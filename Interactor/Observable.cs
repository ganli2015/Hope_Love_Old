using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Interactor
{
    public interface Observable
    {
        void RegisterObserver(ArtificialIntelligences anAI);
        void NotifyObserver();
        void RemoveObserver(ArtificialIntelligences anAI);
        void UpdateCommand();
    }
}
