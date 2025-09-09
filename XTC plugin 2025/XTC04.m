classdef XTC04 < audioPlugin
    properties
        D = 1.0;
        dp = 0.2;
        do = 0.18;
        beta = 0.01;        
    end
    
    properties(Access = private)
        % Propiedades para los objetos de filtro
        pFIRL;
        pFIRR;
        nSamplesIR = 4096;
    end
    
    properties(Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('D', 'DisplayName', 'Distancia Altavoces-Oídos', 'Mapping', {'lin', 0.5, 2}), ...
            audioPluginParameter('dp', 'DisplayName', 'Distancia entre Altavoces', 'Mapping', {'lin', 0.1, 1}), ...
            audioPluginParameter('do', 'DisplayName', 'Distancia entre Oídos', 'Mapping', {'lin', 0.1, 0.3}), ...
            audioPluginParameter('beta', 'DisplayName', 'Regularización β', 'Mapping', {'log', 1e-4, 1e-1}),...
            ...%audioPluginParameter('nSamplesIR', 'DisplayName', 'Muestras IR', 'Mapping', {'lin', 1024, 8192}),
            'InputChannels', 2, ...
            'OutputChannels', 2, ...
            'PluginName', 'CrosstalkConvolver' ...
            );
    end
    
    methods
        function plugin = XTC04()
            % Constructor: se llama una sola vez
            fs = getSampleRate(plugin);
            
            % Generar IR inicial
            [cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir(...
                plugin.D, plugin.dp, plugin.do, plugin.beta, plugin.nSamplesIR, fs);
            
            % Crear los objetos de filtro FIR
            plugin.pFIRL = dsp.FrequencyDomainFIRFilter('Numerator', cLL.');
            plugin.pFIRR = dsp.FrequencyDomainFIRFilter('Numerator', cLR.');
        end
        
        function out = process(plugin, in)
            % Procesar el audio con los objetos de filtro
            out(:,1) = plugin.pFIRL(in(:,1)) + plugin.pFIRR(in(:,2));
            out(:,2) = plugin.pFIRR(in(:,1)) + plugin.pFIRL(in(:,2));
        end
        
        function reset(plugin)
            % Reiniciar los objetos del filtro
            reset(plugin.pFIRL);
            reset(plugin.pFIRR);
        end
        
        function set.D(plugin, val)
            plugin.D = val;
            plugin.updateFilters();
        end
        
        % Incluye los métodos set para dp, do, beta y nSamplesIR
        function set.dp(plugin, val)
            plugin.dp = val;
            plugin.updateFilters();
        end
        
        function set.do(plugin, val)
            plugin.do = val;
            plugin.updateFilters();
        end

        function set.beta(plugin, val)
            plugin.beta = val;
            plugin.updateFilters();
        end

        function set.nSamplesIR(plugin, val)
            allowed = [1024, 2048, 4096, 8192];
            if ~ismember(val, allowed)
                error('nSamplesIR debe ser uno de los siguientes valores: 1024, 2048, 4096, 8192');
            end
            plugin.nSamplesIR = val;
            plugin.updateFilters();
        end

    end
    
    methods(Access = private)
        function updateFilters(plugin)
            % Genera una nueva IR y actualiza los objetos de filtro
            fs = getSampleRate(plugin);
            [cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir(...
                plugin.D, plugin.dp, plugin.do, plugin.beta, plugin.nSamplesIR, fs);
            
            % Actualizar la IR de los filtros
            plugin.pFIRL.Numerator = cLL.';
            plugin.pFIRR.Numerator = cLR.';
        end
    end
end