classdef XTC03 < audioPlugin
    properties
        % Propiedades para los parámetros del plugin
        D = 1.0;
        dp = 0.2;
        do = 0.18;
        beta = 0.01;
        nSamplesIR = 4096;
    end
    
    properties(Access = private)
        % Propiedad privada para almacenar la IR pre-calculada
        ir; 
    end
    
    properties(Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('D', 'DisplayName', 'Distancia Altavoces-Oídos', 'Mapping', {'lin', 0.5, 2}), ...
            audioPluginParameter('dp', 'DisplayName', 'Distancia entre Altavoces', 'Mapping', {'lin', 0.1, 1}), ...
            audioPluginParameter('do', 'DisplayName', 'Distancia entre Oídos', 'Mapping', {'lin', 0.1, 0.3}), ...
            audioPluginParameter('beta', 'DisplayName', 'Regularización β', 'Mapping', {'log', 1e-4, 1e-1}), ...
            audioPluginParameter('nSamplesIR', 'DisplayName', 'Muestras IR', 'Mapping', {'lin', 1024, 8192}), ...
            'InputChannels', 2, ...
            'OutputChannels', 2, ...
            'PluginName', 'CrosstalkConvolver' ...
            );
    end
    
    methods
        function plugin = XTC03()
            % Constructor: se llama una sola vez al inicializar el plugin
            plugin.updateImpulseResponse();
        end
        
        function out = process(plugin, in)
            % Método principal para procesar el audio
            % La convolución en tiempo real con IR grandes es compleja,
            % aquí se usa una convolución simple para demostrar el concepto.
            
            % Separar canales
            xL = in(:,1);
            xR = in(:,2);
            
            % Convolución
            yL = conv(xL, plugin.ir(:, 1), 'same') + conv(xR, plugin.ir(:, 2), 'same');
            yR = conv(xR, plugin.ir(:, 1), 'same') + conv(xL, plugin.ir(:, 2), 'same');
            
            out = [yL, yR];
        end
        
        function reset(plugin)
            % Se llama para resetear el estado del plugin
            plugin.updateImpulseResponse();
        end
        
        function set.D(plugin, val)
            plugin.D = val;
            plugin.updateImpulseResponse();
        end
        
        % Los otros métodos set.dp, set.do, set.beta, set.nSamplesIR
        % deben tener la misma estructura: actualizar la propiedad y luego
        % llamar a updateImpulseResponse().
        function set.dp(plugin, val)
            plugin.dp = val;
            plugin.updateImpulseResponse();
        end
        
        function set.do(plugin, val)
            plugin.do = val;
            plugin.updateImpulseResponse();
        end
        
        function set.beta(plugin, val)
            plugin.beta = val;
            plugin.updateImpulseResponse();
        end
        
        function set.nSamplesIR(plugin, val)
            plugin.nSamplesIR = val;
            plugin.updateImpulseResponse();
        end

    end
    
    methods(Access = private)
        function updateImpulseResponse(plugin)
            % Genera la IR cuando cambian los parámetros
            fs = getSampleRate(plugin);
            [cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir(...
                plugin.D, plugin.dp, plugin.do, plugin.beta, plugin.nSamplesIR, fs);
            
            % Almacena la IR en la propiedad privada
            plugin.ir = [cLL, cLR];
        end
    end
end