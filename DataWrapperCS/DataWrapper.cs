using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using Interactor;

namespace DataWrapperCS
{
    public  class DataWrapper
    {
        static string _inputsentence;
        static string _outputsentence;
        Observable _observable;
        public DataWrapper()
        {
            _inputsentence = null;
        }
        public string outputsentence
        {
            get { return _outputsentence; }
            set { _outputsentence = value; }
        }
        public string Getinputsen()
        {
            return _inputsentence;
        }
        public void Setinputsen(string sentence)
        {
            _inputsentence = sentence;
        }
        public string inputsentence
        {
            get
            {
                return _inputsentence;
            }
            set { _inputsentence = value; }
        }
        public Observable Observable
        {
            get { return _observable; }
            set { _observable = value; }
        }

        public void NotifyObservers()
        {
            _observable.NotifyObserver();
        }
    }
    
}
