set DXC="..\..\External\dxc\bin\x64\dxc.exe"
%DXC% -T vs_6_0 -E main -Fo simple.dxil /Zi simple.hlsl
rem %DXC% -T vs_6_0 -E FpsVS -Fo simple.dxil fps.hlsl
