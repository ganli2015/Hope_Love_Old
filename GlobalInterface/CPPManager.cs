using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GlobalInterface
{
    public interface CPPManager
    {
        void Notify(DataWrapper data);
        void ConnectUI(UIForm form);
        void Execute(DataWrapper data);
        void Kill();
    }
}
