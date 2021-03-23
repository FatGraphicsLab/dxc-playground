set DXC="..\..\External\dxc\bin\x64\dxc.exe"

%DXC% -T vs_6_0 -E main -Fo SimpleVS.dxo -Zi -Fd SimpleVS.pdb -Fre "SimpleVS.ref" -Qstrip_reflect SimpleVS.hlsl
%DXC% -T ps_6_0 -E main -Fo SimplePS.dxo -Zi -Fd SimplePS.pdb -Fre "SimplePS.ref" -Qstrip_reflect SimplePS.hlsl
