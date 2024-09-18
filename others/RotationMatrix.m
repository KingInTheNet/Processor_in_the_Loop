function R = RotationMatrix(i, p)
%#codegen

R = [1 0 0; ...
     0 1 0; ...
     0 0 1];

cp = cos(p);
sp = sin(p);

if i == 1
    R = [1   0  0; ...
         0  cp sp; ...
         0 -sp cp];
end

if i == 2
    R = [cp 0 -sp; ...
          0 1   0; ...
         sp 0  cp];
end

if i == 3
    R = [ cp sp 0; ...
         -sp cp 0; ...
           0  0 1];
end