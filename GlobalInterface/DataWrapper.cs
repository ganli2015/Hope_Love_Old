using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GlobalInterface
{
    public enum DataType
    {
        InputString,
        OutputString
    }

    public interface DataWrapper
    {
        object GetData(DataType type);
        void SetData(DataType type,object data);
    }
}
