clear all
clc

delete *.mexw64

cd library\sfunc_nrlmsise00
delete *.mexw64
cd ..\..

%PWD = pwd;
% addpath(genpath(strcat(pwd, 'library')));
% addpath(genpath(strcat(pwd, 'others')));
% addpath(genpath(strcat(pwd, 'component_communication')));
% addpath(genpath(strcat(pwd, 'AOCS_Process')));

addpath('library')
addpath('library\sfunc_nrlmsise00')
addpath('others')
addpath('component_communication')
addpath('AOCS_Process')
addpath('Development_scratchpad')
folder_list = {'library\sfunc_nrlmsise00','Development_scratchpad','others','component_communication','AOCS_Process'}
for foldernum = 1:length(folder_list)
    folder = string(folder_list(foldernum))
    fprintf(class(folder) + "\n")
    mfiles = dir(fullfile(folder, '*.m'));
    names = fieldnames(mfiles) 
    s = what(folder)

    % fprintf(class(mfiles) + "\n")
    % fprintf(mfiles(1).name)

    for k = 1:length(mfiles)
        file = mfiles(k).name;
        fprintf(file + "\n") 
        if file ~= "close.m"
            try
                % run(append(findfile(folder,file)file)
                run(append(s.path, '\',file))
            catch
                % print message if it failed
                fprintf('failed to run: %s\n', file);
            end
        end
    end
end