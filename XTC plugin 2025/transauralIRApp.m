function transauralIRApp
    % Crear ventana
    fig = uifigure('Name','Generador FIR Crosstalk','Position',[100 100 500 600]);

    plugin = XTC07(); % Instancia del plugin

    % Parámetros físicos
    labels = {'D (m)', 'dp (m)', 'do (m)', 'beta', 'nSamplesIR', 'fs (Hz)'};
    defaults = [0.2, 0.3, 0.18, 0.01, 4096, 0];
    fields = gobjects(1,6);

    for i = 1:6
        uilabel(fig,'Text',labels{i},'Position',[30 590-49*i 100 22]);
        fields(i) = uieditfield(fig,'numeric','Value',defaults(i),...
            'Position',[140 590-49*i 100 22]);
    end

    % Selector de nombre de archivo
    uilabel(fig,'Text','Nombre del archivo WAV','Position',[30 250 150 22]);
    nameField = uieditfield(fig,'text','Value','respuestaImpulsoXTC.wav',...
        'Position',[180 250 200 22]);

    % Selector de carpeta
    uibutton(fig,'Text','Elegir carpeta destino','Position',[30 210 150 22],...
        'ButtonPushedFcn',@(btn,event) seleccionarCarpeta(fig));

    folderLabel = uilabel(fig,'Text','Carpeta: ./','Position',[200 210 250 22]);
    folderLabel.Tag = 'folderPath';

    % Botón para generar archivo
    uibutton(fig,'Text','Generar IR y guardar WAV','Position',[150 160 200 30],...
        'ButtonPushedFcn',@(btn,event) generarIR(fields, nameField, folderLabel, plugin));

    % Axes para visualizar IR
    ax = uiaxes(fig,'Position',[50 20 400 120]);
    ax.Tag = 'plotAxes';
    title(ax,'Respuesta al impulso (L y R)');
    xlabel(ax,'Muestras'); ylabel(ax,'Amplitud');
end

function seleccionarCarpeta(fig)
    path = uigetdir;
    if path ~= 0
        lbl = findobj(fig,'Tag','folderPath');
        lbl.Text = ['Carpeta: ' path];
    end
end

function generarIR(fields, nameField, folderLabel, plugin)
    % Leer valores
    D = fields(1).Value;
    dp = fields(2).Value;
    do = fields(3).Value;
    beta = fields(4).Value;
    nSamplesIR = round(fields(5).Value);
    fs = round(fields(6).Value);

    % Calcular IR
    [cLL, ~, cLR, ~, ~, ~, ~, ~] = transaural_ir2(D,dp,do,beta,nSamplesIR,fs);
    irStereo = [cLL, cLR];

    % Mostrar en gráfico
    ax = findobj(fields(1).Parent,'Tag','plotAxes');
    cla(ax);
    plot(ax, irStereo(:,1), 'b'); hold(ax,'on');
    plot(ax, irStereo(:,2), 'r'); legend(ax,{'Izquierdo','Derecho'});

    % Guardar archivo
    folderPath = strrep(folderLabel.Text,'Carpeta: ','');
    filename = fullfile(folderPath, nameField.Value);
    audiowrite(filename, irStereo, fs);
    plugin.loadWavIRFromPath(filename); % Cargar la IR en el plugin


    if any(isnan(irStereo(:))) || isempty(irStereo)
    uialert(fields(1).Parent, 'La respuesta al impulso no es válida.', 'Error');
    return;
    end

    % Confirmación
    uialert(fields(1).Parent, ['Archivo guardado como "' filename '"'], '¡Listo!', ...
        'Icon','success');
end