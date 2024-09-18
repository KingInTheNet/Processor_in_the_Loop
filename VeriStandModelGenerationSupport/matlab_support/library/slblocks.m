% SLBLOCKS Defines the block library for a specific Toolbox or Blockset.
% https://in.mathworks.com/help/simulink/ug/adding-libraries-to-the-library-browser.html

function blkStruct = slblocks

    Browser(1).Library = 'VeriStandBlocks';

    Browser(1).Name    = 'VeriStand Blocks';

    blkStruct.Browser = Browser;

% End of slblocks