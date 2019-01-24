using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Access = Microsoft.Office.Interop.Access;
using System.Runtime.InteropServices;


namespace AccessExportTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Access.Application accessApp = null;
            //Access.DoCmd doCmdDisp = null;
            Access.AllObjects allTblsDisp = null;

            try
            {
                accessApp = new Access.Application();
                accessApp.OpenCurrentDatabase(args[0]);

                //doCmdDisp = accessApp.DoCmd;
                allTblsDisp = accessApp.CurrentData.AllTables;
                
                long tableCnt = allTblsDisp.Count;

                System.Collections.IEnumerator tblEnumerator = allTblsDisp.GetEnumerator();
                Access.AccessObject tableObj = null;
                List<string> tblList = new List<string>();
                while (tblEnumerator.MoveNext())
                {
                    tableObj = (Access.AccessObject)tblEnumerator.Current;
                    tblList.Add(tableObj.Name);
                }

                int progressGauge = 0;
                Stopwatch stopWatch = new Stopwatch();

                foreach (string tblName in tblList)
                {
                    //doCmdDisp.TransferText(Access.AcTextTransferType.acExportDelim, tmpObj, tblName, args[1] + tblName + ".csv");
                    accessApp.ExportXML(Access.AcExportXMLObjectType.acExportTable, tblName, args[1] + tblName + ".xml");

                    Console.Write("Convert MDB to XML... {0}%\r", progressGauge * 100 / tblList.Count + 1);
                    ++progressGauge;
                }

                stopWatch.Stop();
                Console.WriteLine(stopWatch.ElapsedMilliseconds.ToString() + "ms");
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            finally
            {
                accessApp.Quit(Access.AcQuitOption.acQuitSaveNone);
                accessApp = null;
            }
        }
    }

}
