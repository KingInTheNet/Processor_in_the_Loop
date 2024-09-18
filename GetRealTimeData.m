function [Pbat, Bsoc, Pgrid, Ppv, load, frequency]=GetRealTimeData(batteryCDpower)
    % Get data from Simulink  
       % Select the RuntimeObject
       set_param('CaseA18/sc_user_interface/Embedded MATLAB Function','selected','on') % without OPAL-RT RTDS
       % set_param('casea18_2_sc_user_interface/Embedded MATLAB Function','selected','on')
       % Get data from RuntimeObject
       rto = get_param(gcb,'RunTimeObject');
       Pbat=rto.OutputPort(1).Data;
       Bsoc=rto.OutputPort(2).Data;
       
       Pgrid=rto.OutputPort(3).Data;
       Ppv=rto.OutputPort(4).Data;
       load=rto.OutputPort(5).Data;
       
       frequency=rto.OutputPort(6).Data;
       
    % Get data to Simulink   
        set_param('CaseA18/sc_user_interface/Constant','Value','batteryCDpower');% without OPAL-RT RTDS
       %set_param('casea18_2_sc_user_interface/Constant','Value','batteryCDpower')
   end