classdef XTC_Processor < matlab.System
% XTC_Processor Core DSP engine for the crosstalk cancellation plugin.
% This class is designed for C++ code generation.

    % --- Properties ---
    properties (Access = private)
        % Filter objects for each convolution path.
        % They are initialized in the constructor to define their type for Coder.
        pFilter_LL
        pFilter_RL
        pFilter_LR
        pFilter_RR
        
        % This property will store the last used parameters to check for changes.
        pLastParams
    end
    
    properties (Access = private, Nontunable)
        % Nontunable properties define the structure and cannot change at runtime.
        nSamplesIR = 8192; % Fixed impulse response length
    end

    % --- Methods ---
    methods
        % --- CONSTRUCTOR ---
        function obj = XTC_Processor()
            % The constructor pre-initializes the filter properties.
            % This tells MATLAB Coder the exact class of each property upfront,
            % preventing type-mismatch errors during code generation.
            obj.pFilter_LL = dsp.FrequencyDomainFIRFilter;
            obj.pFilter_RL = dsp.FrequencyDomainFIRFilter;
            obj.pFilter_LR = dsp.FrequencyDomainFIRFilter;
            obj.pFilter_RR = dsp.FrequencyDomainFIRFilter;

            obj.pLastParams = struct( ...
                'D', 0.0, ...
                'dp', 0.0, ...
                'do', 0.0, ...
                'beta', 0.0, ...
                'SampleRate', 0.0);

        end
    end

    methods (Access = protected)
        % --- SETUP ---
        function setupImpl(obj, ~, params)
            % Called once at the beginning. We do an initial calculation here.
            recalculateFilters(obj, params);
        end

        % --- PROCESS ---
        function out = stepImpl(obj, in, params)
            % Called for each block of audio.
            
            % --- Parameter Update Check ---
            % This is the standard way to handle tunable parameters.
            % We only recalculate the filters if the params struct has changed.
            if isempty(obj.pLastParams) || ~isequal(obj.pLastParams, params)
                recalculateFilters(obj, params);
                obj.pLastParams = params;
            end
            
            % --- Audio Processing ---
            left_in  = in(:, 1);
            right_in = in(:, 2);

            % Process each path through its dedicated filter
            y_LL = step(obj.pFilter_LL, left_in);
            y_RL = step(obj.pFilter_RL, left_in);
            y_LR = step(obj.pFilter_LR, right_in);
            y_RR = step(obj.pFilter_RR, right_in);

            % Combine the results
            out_L = y_LL + y_LR;
            out_R = y_RL + y_RR;
            
            out = [out_L, out_R];
        end
        
        % --- PRIVATE HELPER METHOD ---
        function recalculateFilters(obj, params)
            % This private method contains the logic to update filter coefficients.
            
            % Recalculate the impulse responses with the new parameters
            [cLL, cLR] = transaural_ir(...
                params.D, params.dp, params.do, params.beta, ...
                obj.nSamplesIR, params.SampleRate);
            
            % Update the Numerator of the existing filter objects
            obj.pFilter_LL.Numerator = cLL.';
            obj.pFilter_RL.Numerator = cLR.';
            obj.pFilter_LR.Numerator = cLR.';
            obj.pFilter_RR.Numerator = cLL.';
        end
    end
end