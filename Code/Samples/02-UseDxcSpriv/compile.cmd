set DXC="..\..\External\dxc\bin\x64\dxc.exe"

%DXC% -spirv -T vs_6_0 -E main -Fo SimpleVS.dxo SimpleVS.hlsl
%DXC% -spirv -T ps_6_0 -E main -Fo SimplePS.dxo SimplePS.hlsl
