classdef XTC07 < audioPlugin
    
    properties
        D = 1.0;
        dp = 0.2;
        do = 0.18;
        beta = 0.01;
        loadIR_Enum = 'No';
    end
    
    properties(Access = private)        
        pFilter_LL; pFilter_RL; pFilter_LR; pFilter_RR;        
        nSamplesIR = 8192;
        pWavIR=[];
    end
    
    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('D', 'DisplayName', 'Distancia Altavoces-Oídos (m)', 'Mapping', {'lin', 0.5, 2}), ...
            audioPluginParameter('dp', 'DisplayName', 'Distancia entre Altavoces (m)', 'Mapping', {'lin', 0.1, 1}), ...
            audioPluginParameter('do', 'DisplayName', 'Distancia entre Oídos (m)', 'Mapping', {'lin', 0.1, 0.3}), ...
            audioPluginParameter('beta', 'DisplayName', 'Regularización ?', 'Mapping', {'log', 1e-4, 1e-1}),...
            audioPluginParameter('loadIR_Enum', 'DisplayName', 'Cargar IR (WAV)', 'Mapping', {'enum', 'No','Sí'}), ...
            'InputChannels', 2, ...
            'OutputChannels', 2, ...
            'PluginName', 'CrosstalkConvolver' ...
            );
    end
    
    methods
        function plugin = XTC07()
            plugin.updateFilters();
        end
        
        function out = process(plugin, in)
            if isempty(plugin.pFilter_LL) % Chequeo de seguridad
                out = in;
                return;
            end
            
            left_in = in(:,1);
            right_in = in(:,2);
            
            % %% CAMBIO CLAVE: Lógica de procesamiento correcta usando 4 filtros.
            % Cada filtro se llama UNA SOLA VEZ por bloque.
            y_LL = plugin.pFilter_LL(left_in);
            y_RL = plugin.pFilter_RL(right_in);
            
            y_LR = plugin.pFilter_LR(left_in);
            y_RR = plugin.pFilter_RR(right_in);
            
            % Sumar las salidas para cada canal
            outL = y_LL + y_RL;
            outR = y_LR + y_RR;
            
            out = [outL, outR];
        end
        
        function reset(plugin)
            % Reiniciar los 4 filtros
            if ~isempty(plugin.pFilter_LL)
                reset(plugin.pFilter_LL);
                reset(plugin.pFilter_RL);
                reset(plugin.pFilter_LR);
                reset(plugin.pFilter_RR);
            end
        end
        
        % --- MÉTODOS 'SET' PARA ACTUALIZAR PARÁMETROS ---
        function set.D(plugin, val)
            plugin.D = val;
            plugin.updateFilters();
        end
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
        function set.loadIR_Enum(plugin, val)
            plugin.loadIR_Enum = val;
            if strcmp(val, 'Sí')
                plugin.loadWavIR(); 
            end
            plugin.updateFilters();
        end
    end

    methods (Access = private)
         function updateFilters(plugin)
             fs = getSampleRate(plugin);
             if fs == 0, return; end
             
             % Obtener las respuestas al impulso (ipsilateral cLL y contralateral cLR)
             if strcmp(plugin.loadIR_Enum, 'Sí') && ~isempty(plugin.pWavIR)
                 ir_data = plugin.pWavIR;
                 len = min(plugin.nSamplesIR, size(ir_data, 1));
                 cLL = zeros(plugin.nSamplesIR, 1);
                 cLR = zeros(plugin.nSamplesIR, 1);
                 cLL(1:len) = ir_data(1:len, 1);
                 cLR(1:len) = ir_data(1:len, 2);
             else
                 [cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir2(...
                     plugin.D, plugin.dp, plugin.do, plugin.beta, plugin.nSamplesIR, fs);
             end
             
             plugin.pFilter_LL = dsp.FrequencyDomainFIRFilter(...
                'Numerator', cLL.');             
             plugin.pFilter_RL = dsp.FrequencyDomainFIRFilter(...
                'Numerator', cLR.');             
             plugin.pFilter_LR = dsp.FrequencyDomainFIRFilter(...
                'Numerator', cLR.');             
             plugin.pFilter_RR = dsp.FrequencyDomainFIRFilter(...
                'Numerator', cLL.');
         end
         
         function loadWavIR(plugin)
             [filename, pathname] = uigetfile('*.wav', 'Seleccionar Archivo de Respuesta al Impulso (Estéreo)');        
             if ischar(filename)
                filepath = fullfile(pathname, filename);            
                try
                    [ir_data, Fs] = audioread(filepath);                
                    if size(ir_data, 2) ~= 2
                        warning('El archivo WAV debe ser estéreo.');
                        plugin.pWavIR = []; return;
                    end
                    if Fs ~= getSampleRate(plugin)
                        warning('Fs del WAV no coincide. Remuestreando...');
                        ir_data = resample(ir_data, getSampleRate(plugin), Fs);
                    end
                    % Primero la limpiamos por si había una IR anterior.
                    plugin.pWavIR(:) = 0; 
                    % Calculamos cuántas muestras copiar (para no exceder el tamaño)
                    lenToCopy = min(size(ir_data, 1), plugin.nSamplesIR);
                    % Copiamos los datos
                    plugin.pWavIR(1:lenToCopy, :) = ir_data(1:lenToCopy, :);
                    disp('IR cargada correctamente desde el archivo WAV.');
                catch ME
                    warning(['Error al cargar el archivo: ', ME.message]);
                    plugin.pWavIR = [];
                end
            else
                plugin.loadIR_Enum = 'No';
            end
            plugin.updateFilters();
         end         
    end    
end