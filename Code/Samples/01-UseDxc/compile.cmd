set DXC="..\..\External\dxc\bin\x64\dxc.exe"
%DXC% -T vs_6_0 -E main -Fo SimpleVS.dxil SimpleVS.hlsl
%DXC% -T ps_6_0 -E main -Fo SimplePS.dxil SimplePS.hlsl
