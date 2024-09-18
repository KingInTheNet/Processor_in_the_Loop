function veristand_make_rtw_hook(hookMethod, modelName, rtwRoot, templateMakefile, buildOpts, buildArgs, buildInfo)
    veriStandTlcVsmodel = VeriStandTlcVsmodel;
    veriStandTlcVsmodel.MakeRtwHook(hookMethod, modelName, buildInfo, 'veristand.tlc');
end

