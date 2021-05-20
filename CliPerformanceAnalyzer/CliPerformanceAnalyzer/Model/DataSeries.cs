using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CliPerformanceAnalyzer
{
    #region - Performance Data Model
    public class DataSeries
    {
        public String TargetName { get; set; }
        public IEnumerable<Data> Values { get; set; }
    }

    public class Data
    {
        public string TestName { get; set; }
        public double Value { get; set; }
    }
    #endregion
}
