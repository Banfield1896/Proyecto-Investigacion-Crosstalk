classdef XTC06 < audioPlugin
    % XTC05 - Crosstalk Cancellation Audio Plugin
    % Versi�n corregida para evitar glitches durante la actualizaci�n de par�metros.

    properties
        D = 1.0;
        dp = 0.2;
        do = 0.18;
        beta = 0.01;
        loadIR_Enum = 'No'; % Usamos un nombre diferente para el par�metro enum
    end
    
    properties(Access = private)
        % Propiedades para los objetos de filtro
        pFIRL;
        pFIRR;
        
        % Propiedades para la IR
        nSamplesIR = 4096;
        pWavIR; % Almacena la IR cargada desde el archivo WAV
    end
    
    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('D', 'DisplayName', 'Distancia Altavoces-O�dos (m)', 'Mapping', {'lin', 0.5, 2}), ...
            audioPluginParameter('dp', 'DisplayName', 'Distancia entre Altavoces (m)', 'Mapping', {'lin', 0.1, 1}), ...
            audioPluginParameter('do', 'DisplayName', 'Distancia entre O�dos (m)', 'Mapping', {'lin', 0.1, 0.3}), ...
            audioPluginParameter('beta', 'DisplayName', 'Regularizaci�n ?', 'Mapping', {'log', 1e-4, 1e-1}),...
            audioPluginParameter('loadIR_Enum', 'DisplayName', 'Cargar IR (WAV)', 'Mapping', {'enum', 'No','S�'}), ...
            'InputChannels', 2, ...
            'OutputChannels', 2, ...
            'PluginName', 'CrosstalkConvolver' ...
            );
    end
    
    methods
        function plugin = XTC06()
            % Constructor: se llama una sola vez al inicio
            plugin.updateFilters(); % Llama a updateFilters para la inicializaci�n
        end
        
        function out = process(plugin, in)
            % Bypass si los filtros no est�n listos (no deber�a pasar)
            if isempty(plugin.pFIRL) || isempty(plugin.pFIRR)
                out = in;
                return;
            end
            
            % Procesamiento de la se�al est�reo
            % Canal Izquierdo: L_in * H_LL + R_in * H_RL
            % Canal Derecho: L_in * H_LR + R_in * H_RR
            % Por simetr�a: H_LL=H_RR y H_LR=H_RL.
            % Usamos pFIRL para el filtro ipsilateral (LL) y pFIRR para el contralateral (LR).
            
            outL = plugin.pFIRL(in(:,1)) + plugin.pFIRR(in(:,2));
            outR = plugin.pFIRR(in(:,1)) + plugin.pFIRL(in(:,2));
            
            out = [outL, outR];
        end
        
        function reset(plugin)
            % Reiniciar los objetos del filtro al dar play
            if ~isempty(plugin.pFIRL)
                reset(plugin.pFIRL);
            end
            if ~isempty(plugin.pFIRR)
                reset(plugin.pFIRR);
            end
        end
        
        % --- M�TODOS 'SET' PARA ACTUALIZAR PAR�METROS ---
        
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
            if strcmp(val, 'S�')
                % Si el usuario selecciona 'S�', abrimos el di�logo de archivo
                plugin.loadWavIR(); 
            end
            % Actualizamos los filtros independientemente de si se carg� un archivo o no
            plugin.updateFilters();
        end
        
    end

    methods (Access = private)
         function updateFilters(plugin)
             fs = getSampleRate(plugin);
             % Evitar ejecuci�n si la frecuencia de muestreo a�n no est� definida
             if fs == 0
                 return;
             end
             
             cLL = zeros(plugin.nSamplesIR, 1);
             cLR = zeros(plugin.nSamplesIR, 1);
             
             % Condici�n: �Usamos la IR del WAV o la calculamos?
             if strcmp(plugin.loadIR_Enum, 'S�') && ~isempty(plugin.pWavIR)
                 % Usar la IR previamente cargada desde el archivo WAV
                 ir_data = plugin.pWavIR;
                 len = min(plugin.nSamplesIR, size(ir_data, 1));
                 cLL(1:len) = ir_data(1:len, 1); % Usamos el canal 1 para el filtro ipsilateral
                 cLR(1:len) = ir_data(1:len, 2); % Usamos el canal 2 para el filtro contralateral
             else
                 % Calcular la IR con la funci�n transaural_ir
                 [cLL_calc, ~, cLR_calc, ~, ~, ~, ~, ~] = transaural_ir2(...
                     plugin.D, plugin.dp, plugin.do, plugin.beta, plugin.nSamplesIR, fs);
                 cLL = cLL_calc;
                 cLR = cLR_calc;
             end
             
             % %% CAMBIO CR�TICO: RE-CREAR LOS OBJETOS DE FILTRO
             % En lugar de modificar la propiedad .Numerator, creamos nuevas
             % instancias de los filtros. Esto resetea su estado interno y
             % evita los glitches.
             
             % La longitud de la partici�n debe ser una potencia de 2 y
             % generalmente m�s peque�a que la longitud del IR para
             % controlar la latencia. 512 es un buen punto de partida.
             partitionLength = 512; 
             
             plugin.pFIRL = dsp.FrequencyDomainFIRFilter(...
                'Numerator', cLL.', ...
                'PartitionForReducedLatency', true, ...
                'PartitionLength', partitionLength);
            
             plugin.pFIRR = dsp.FrequencyDomainFIRFilter(...
                'Numerator', cLR.', ...
                'PartitionForReducedLatency', true, ...
                'PartitionLength', partitionLength);
         end
         
         function loadWavIR(plugin)
             % Abrir una ventana de di�logo para seleccionar un archivo WAV
             [filename, pathname] = uigetfile('*.wav', 'Seleccionar Archivo de Respuesta al Impulso (Est�reo)');        
             
             if ischar(filename) % Si el usuario seleccion� un archivo
                 filepath = fullfile(pathname, filename);            
                 try
                     [ir_data, Fs] = audioread(filepath);                
                     
                     if size(ir_data, 2) ~= 2
                         warning('El archivo WAV debe ser est�reo.');
                         plugin.pWavIR = []; % Limpiar la IR guardada
                         return;
                     end
                     
                     if Fs ~= getSampleRate(plugin)
                         warning('La frecuencia de muestreo del WAV no coincide con la del plugin. Se intentar� remuestrear.');
                         ir_data = resample(ir_data, getSampleRate(plugin), Fs);
                     end
                     
                     plugin.pWavIR = ir_data; % Guardar la IR en la propiedad
                     disp('IR cargada correctamente desde el archivo WAV.');
                     
                 catch ME
                     warning(['Error al cargar el archivo: ', ME.message]);
                     plugin.pWavIR = []; % Limpiar en caso de error
                 end
             else
                 % El usuario cancel� la selecci�n. Volvemos al modo 'No'.
                 plugin.loadIR_Enum = 'No';
             end
             
             % Llamamos a updateFilters para aplicar los cambios (ya sea la nueva IR o volver a la calculada)
             plugin.updateFilters();
         end         
    end    
end
