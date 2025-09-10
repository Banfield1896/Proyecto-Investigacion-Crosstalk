function out = xtc_wrapper(in, params)
%xtc_wrapper Entry-point function for MATLAB Coder.
%   This function creates and manages a persistent instance of the
%   XTC_Processor class.

    % Declare 'processor' as persistent so it retains its state
    % between calls.
    persistent processor;
    
    % On the very first call, create and initialize the processor object.
    if isempty(processor)
        processor = XTC_Processor;
        % The setup method will be called automatically by Coder before the
        % first call to 'step'.
    end
    
    % Call the step method of the processor object.
    % The XTC_Processor class itself will handle checking if parameters
    % have changed and recalculating the filters if necessary.
    out = step(processor, in, params);

end