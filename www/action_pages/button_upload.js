function procurarPNG(texto) {
    texto = texto.toLowerCase();

    if (texto.indexOf("png") !== -1) {
        return "png"; 
    } else if (texto.indexOf("jpg") !== -1) {
        return "jpg"; 
    }
}

function uploadSingleFile() {
    var formData = new FormData();
    var fileInput = document.getElementById('singleFileInput');
    formData.append('example', fileInput.files[0]);

    var xhr = new XMLHttpRequest();

    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4) {
            if (xhr.status === 201) 
            {
                var fileName = xhr.responseText;
                var filenameHeader = xhr.getResponseHeader('Filename');
                var fileName = filenameHeader || xhr.responseText;

                console.log(fileName);


                var tbody = document.getElementById('fileList');
                var row = document.createElement('tr');

                var nomeColuna = document.createElement('td');
                nomeColuna.textContent = fileName;
                var tipoColuna = document.createElement('td');
                tipoColuna.textContent = procurarPNG(fileName);
                var tamanhoColuna = document.createElement('td');
                var fileSize = fileInput.files[0].size;
                tamanhoColuna.textContent = fileSize + " Bytes";
                var urls = "http://localhost:8080/uploads/"
                var remove_file = urls + fileName;
                var butao = document.createElement('button');
                butao.textContent = "Delete";
                
                row.appendChild(nomeColuna);
                row.appendChild(tipoColuna);
                row.appendChild(tamanhoColuna);
                row.appendChild(butao);

                tbody.appendChild(row);

                butao.onclick = function() {
                    deleteFile(row, remove_file);
                }
            } else {
                console.error('Erro na solicitaçãos:', xhr.status);
            }
        }
    };
    
    xhr.open('POST', '/uploads', true);
    xhr.send(formData);
}

function deleteFile(row, url) {
    var xhr = new XMLHttpRequest();
    xhr.open("DELETE", url, true);
    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 204) {
            alert("Arquivo excluído com sucesso!");

            // Remover a linha da tabela
            var tbody = document.getElementById('fileList');
            tbody.removeChild(row);
        }
    };
    console.log(url);
    xhr.send();
}

function multipleFile()
{
    event.preventDefault();

    var formData = new FormData();
    var fileInput = document.getElementById('multipleFileInput');

    for (var i = 0; i < fileInput.files.length; i++) {
        formData.append('example[]', fileInput.files[i]);
        console.log(fileInput.files[i].name);
    }

    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () 
    {
        if (xhr.readyState === 4) 
        {
            if (xhr.status === 201) 
            {
                for(var j = 0; j < fileInput.files.length; j++)
                (function (file) {
                    var tbody = document.getElementById('fileList');
                    var row = document.createElement('tr');
                    var nomeColuna = document.createElement('td');
                    nomeColuna.textContent = fileInput.files[j].name;
                    var tipoColuna = document.createElement('td');
                    tipoColuna.textContent = procurarPNG(fileInput.files[j].name);
                    var tamanhoColuna = document.createElement('td');
                    var fileSize = fileInput.files[j].size;
                    tamanhoColuna.textContent = fileSize + " Bytes";
                    var urls = "http://localhost:8080/uploads/"
                    var remove_file = urls + fileInput.files[j].name;
                    var butao = document.createElement('button');
                    butao.textContent = "Delete";
                    
                    row.appendChild(nomeColuna);
                    row.appendChild(tipoColuna);
                    row.appendChild(tamanhoColuna);
                    row.appendChild(butao);
    
                    tbody.appendChild(row);
    
                    butao.onclick = function() 
                    {
                        deleteFile(row, remove_file);
                    }
                })(fileInput.files[j]);
            }  
            else 
            {
                console.error('Erro na solicitaçãos:', xhr.status);
            }
        }
    };
    
    xhr.open('POST', '/uploads', true);
    xhr.send(formData);
}
