using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using ManageWrapper;
using DataWrapperCS;
using System.Runtime.InteropServices;
//using DataWrapperCS;

namespace Interactor
{
    public class InteractorHL:Observable
    {
        private ArrayList _AIset;
        private ManageClass _manageclass;

        public InteractorHL()
        {
            _AIset = new ArrayList();
            _manageclass =new ManageClass();
        }
        public void RegisterObserver(ArtificialIntelligences anAI)
        {
            _AIset.Add(anAI);
        }
        public void NotifyObserver()
        {
            foreach(ArtificialIntelligences anAI in _AIset)
            {
                anAI.UpdateUI();
            }
        }
        public void RemoveObserver(ArtificialIntelligences anAI)
        {
            int i = _AIset.IndexOf(anAI);
            if (i >= 0)
            {
                _AIset.Remove(i);
            }
        }
        public void UpdateCommand()
        {
//             _manageclass.inputsentence = "我是谁";
//             _manageclass.TransportDataFromCStoCPP();
            _manageclass.UpdateCommand();
            NotifyObserver();
        }
    }
}
