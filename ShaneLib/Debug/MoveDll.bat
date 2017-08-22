IF EXIST "C:\Users\shaneh\Documents\Visual Studio 2010\Projects\TestDLL\TestDLL\bin\Debug\ShaneLib.dll". (
  DEL "C:\Users\shaneh\Documents\Visual Studio 2010\Projects\TestDLL\TestDLL\bin\Debug\ShaneLib.dll"
)

IF EXIST "C:\Users\shaneh\Documents\visual studio 2010\Projects\ShaneLibWrapper\ShaneLibWrapper\bin\Debug\ShaneLib.dll". (
  DEL "C:\Users\shaneh\Documents\visual studio 2010\Projects\ShaneLibWrapper\ShaneLibWrapper\bin\Debug\ShaneLib.dll"
)

COPY /B ".\ShaneLib.dll" "C:\Users\shaneh\Documents\Visual Studio 2010\Projects\TestDLL\TestDLL\bin\Debug\ShaneLib.dll"
COPY /B ".\ShaneLib.dll" "C:\Users\shaneh\Documents\visual studio 2010\Projects\ShaneLibWrapper\ShaneLibWrapper\bin\Debug\ShaneLib.dll"
pause