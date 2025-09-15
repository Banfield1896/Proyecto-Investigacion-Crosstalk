classdef XTC07 < audioPlugin
    
    properties
        D = 1.0;
        dp = 0.2;
        do = 0.18;
        beta = 0.01;
    end
    
    properties(Access = private)
        % Coeficientes como vectores fila
        cLL = zeros(1, 8192);
        cLR = zeros(1, 8192);
        
        % FIX: Los estados ahora son VECTORES COLUMNA (mono)
        zLL = zeros(8191, 1);
        zLR = zeros(8191, 1);
        zRL = zeros(8191, 1);
        zRR = zeros(8191, 1);
    end

    properties (Constant, Access = private)
        nSamplesIR = 8192;
    end
    
    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('D', 'DisplayName', 'Distancia Altavoces-Oídos (m)', 'Mapping', {'lin', 0.1, 2}), ...
            audioPluginParameter('dp', 'DisplayName', 'Distancia entre Altavoces (m)', 'Mapping', {'lin', 0.1, 1}), ...
            audioPluginParameter('do', 'DisplayName', 'Distancia entre Oídos (m)', 'Mapping', {'lin', 0.1, 0.3}), ...
            audioPluginParameter('beta', 'DisplayName', 'Regularización β', 'Mapping', {'log', 1e-4, 1e-1}),...
            'InputChannels', 2, ...
            'OutputChannels', 2, ...
            'PluginName', 'CrosstalkConvolver' ...
            );
    end
    
    methods
        function plugin = XTC07()
            plugin.reset();
        end
        
        function out = process(plugin, in)
            left_in = in(:,1);
            right_in = in(:,2);

            [y_LL, plugin.zLL] = filter(plugin.cLL, 1, left_in, plugin.zLL);
            [y_RL, plugin.zRL] = filter(plugin.cLR, 1, right_in, plugin.zRL);
            
            [y_LR, plugin.zLR] = filter(plugin.cLR, 1, left_in, plugin.zLR);
            [y_RR, plugin.zRR] = filter(plugin.cLL, 1, right_in, plugin.zRR);
            
            outL = y_LL + y_RL;
            outR = y_LR + y_RR;
            
            out = [outL, outR];
        end
        
        function reset(plugin)
            % FIX: Se resetean los estados a vectores columna (mono)
            plugin.zLL = zeros(plugin.nSamplesIR - 1, 1);
            plugin.zLR = zeros(plugin.nSamplesIR - 1, 1);
            plugin.zRL = zeros(plugin.nSamplesIR - 1, 1);
            plugin.zRR = zeros(plugin.nSamplesIR - 1, 1);
            
            plugin.updateCoefficients();
        end
        
        % --- Métodos SET ---
        function set.D(plugin, val)
            plugin.D = val;
            plugin.updateCoefficients();
        end
        function set.dp(plugin, val)
            plugin.dp = val;
            plugin.updateCoefficients();
        end
        function set.do(plugin, val)
            plugin.do = val;
            plugin.updateCoefficients();
        end
        function set.beta(plugin, val)
            plugin.beta = val;
            plugin.updateCoefficients();
        end
    end

    methods (Access = private)
         function updateCoefficients(plugin)
             fs = getSampleRate(plugin);
             if fs == 0, return; end
             
             [cLL_temp, cLR_temp] = transaural_ir(plugin.D, plugin.dp, plugin.do,...
                 plugin.beta, plugin.nSamplesIR, fs);             
             
             plugin.cLL = cLL_temp.';
             plugin.cLR = cLR_temp.';
         end
    end    
end