using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GlobalInterface
{
    public interface UIForm
    {
        void UpdateCommand(DataWrapper data);
        void Register(CPPManager manager);
        void UpdateUI(DataWrapper data);
    }
}
