classdef XTC05 < audioPlugin
    properties
        D = 1.0;
        dp = 0.2;
        do = 0.18;
        beta = 0.01;
        loadIR = false
    end
    
    properties(Access = private)
        % Propiedades para los objetos de filtro
        pFIRL;
        pFIRR;
        nSamplesIR = 8192;
        pWavIR;
    end
    
    properties(Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('D', 'DisplayName', 'Distancia Altavoces-Oídos', 'Mapping', {'lin', 0.5, 2}), ...
            audioPluginParameter('dp', 'DisplayName', 'Distancia entre Altavoces', 'Mapping', {'lin', 0.1, 1}), ...
            audioPluginParameter('do', 'DisplayName', 'Distancia entre Oídos', 'Mapping', {'lin', 0.1, 0.3}), ...
            audioPluginParameter('beta', 'DisplayName', 'Regularización β', 'Mapping', {'log', 1e-4, 1e-1}),...
            audioPluginParameter('loadIR', 'DisplayName', 'Cargar IR (WAV)', 'Mapping', {'enum', 'No','Sí'}), ... % Nuevo botón
            ...%audioPluginParameter('nSamplesIR', 'DisplayName', 'Muestras IR', 'Mapping', {'lin', 1024, 8192}),
            'InputChannels', 2, ...
            'OutputChannels', 2, ...
            'PluginName', 'CrosstalkConvolver' ...
            );
    end
    
    methods
        function out = process(plugin, in)
            nChannels = size(in,2);
            out = zeros(size(in));
            debugOutL = plugin.pFIRL(in(:,1));
            debugOutR = plugin.pFIRR(in(:,2));
            % Procesar el audio con los objetos de filtro
            if nChannels == 1
                out(:,1) = plugin.pFIRL(in(:,1)) + plugin.pFIRR(in(:,1));
                out(:,2) = plugin.pFIRR(in(:,1)) + plugin.pFIRL(in(:,1));
            elseif nChannels >= 2               
                %out(:,1) = plugin.pFIRR(in(:,1)) + plugin.pFIRL(in(:,2));
                %out(:,2) = plugin.pFIRL(in(:,1)) + plugin.pFIRR(in(:,2));
                out(:,1) = plugin.pFIRL(in(:,1)) + plugin.pFIRR(in(:,2));
                out(:,2) = plugin.pFIRR(in(:,1)) + plugin.pFIRL(in(:,2));
            elseif isempty(plugin.pFIRL) || isempty(plugin.pFIRR)
                out = in; % Bypass si no est�n listos
                return;
            end            
        end
        
        function plugin = XTC05()
            % Constructor: se llama una sola vez
            fs = getSampleRate(plugin);
            %partitionLength = 512;  % Ajustable seg�n latencia deseada            
            % Generar IR inicial
            [cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir(...
                plugin.D, plugin.dp, plugin.do, plugin.beta, plugin.nSamplesIR, fs);            
            % Crear los objetos de filtro FIR
            plugin.pFIRL = dsp.FrequencyDomainFIRFilter( ...
                'PartitionForReducedLatency', true, ...
                'PartitionLength', plugin.nSamplesIR, 'Numerator', cLL.');
            plugin.pFIRR = dsp.FrequencyDomainFIRFilter( ...
                'PartitionForReducedLatency', true, ...
                'PartitionLength', plugin.nSamplesIR, 'Numerator', cLR.'); 
            disp(['PartitionLength L: ', num2str(plugin.pFIRL.PartitionLength)]);
            disp(['PartitionLength R: ', num2str(plugin.pFIRR.PartitionLength)]);
            disp(['IR size L: ', num2str(length(plugin.pFIRL.Numerator))]);
            disp(['IR size R: ', num2str(length(plugin.pFIRR.Numerator))]);
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

        function set.loadIR(plugin, val)
            plugin.loadIR = val;
            plugin.updateFilters();  % Esto fuerza la actualizaci�n de filtros
        end
        
        % Este método debe estar aquí, en el mismo bloque que los set.
        %function setParameterValue(plugin, parameterName, value)
        %    if strcmp(parameterName, 'loadIR') && value == 2 % 'Sí' es el segundo valor
        %        plugin.loadWavIR();
        %    else
                % otros parámetros
        %    end
        %end

        function loadWavIRFromPath(plugin, filepath)
            [ir_data, Fs] = audioread(filepath);
            if size(ir_data,2)==2 && Fs==getSampleRate(plugin)
                plugin.pWavIR = ir_data;
                plugin.updateFilters();
            else
                disp('Archivo inválido');
            end
        end    

    end % Fin del bloque 'methods'
  

    methods (Access = private)
         function updateFilters(plugin)
             fs = getSampleRate(plugin);
             if plugin.loadIR && ~isempty(plugin.pWavIR)                
                 plugin.pFIRL.Numerator = plugin.pWavIR(:, 1).';
                 plugin.pFIRR.Numerator = plugin.pWavIR(:, 2).';                
             else                
                 [cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir(...
                     plugin.D, plugin.dp, plugin.do, plugin.beta, plugin.nSamplesIR, fs);
            
                 plugin.pFIRL.Numerator = cLL.';
                 plugin.pFIRR.Numerator = cLR.';
             end
         end
         
         function loadWavIR(plugin)
             % Abrir una ventana de diálogo para que el usuario seleccione un archivo WAV
             [filename, pathname] = uigetfile('*.wav', 'Seleccionar Archivo de Respuesta al Impulso');        
             % Si el usuario selecciona un archivo
             if ischar(filename)
                 filepath = fullfile(pathname, filename);            
                 try
                     % Cargar el archivo WAV
                     [ir_data, Fs] = audioread(filepath);                
                     % Verificar si la IR tiene 2 canales y coincide la Fs del plugin
                     if size(ir_data, 2) == 2 && Fs == getSampleRate(plugin)
                         plugin.pWavIR = ir_data;
                         plugin.updateFilters(); % Actualizar los filtros con la nueva IR
                     else
                         % Mostrar un error si el archivo no es válido
                         % En un plugin, no se puede usar `error` directamente. 
                         % Es mejor mostrar un mensaje de depuración.
                         disp('Error: El archivo WAV debe ser estéreo y tener la misma Fs que el plugin.');
                     end
                 catch ME
                     % Manejar cualquier error de lectura del archivo
                     disp(['Error al cargar el archivo: ', ME.message]);
                 end
             end
         end         
    end    
end