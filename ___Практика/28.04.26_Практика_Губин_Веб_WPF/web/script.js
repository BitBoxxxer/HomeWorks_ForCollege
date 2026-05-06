async function loadTemperatures() {
    try {
        const response = await fetch('/api/temperature');
        if (!response.ok) throw new Error('Ошибка сервера');
        const data = await response.json();
        const tbody = document.getElementById('tempBody');
        
        if (data.length === 0) {
            tbody.innerHTML = '<tr><td colspan="2">📭 Нет данных. Запустите WPF-датчик.</td></tr>';
            return;
        }
        
        tbody.innerHTML = data.map(record => `
            <tr>
                <td style="font-weight: bold;">${record.temperature.toFixed(1)} °C</td>
                <td>${new Date(record.timestamp).toLocaleString()}</td>
            </tr>
        `).join('');
    } catch (err) {
        console.error('Ошибка загрузки:', err);
        const tbody = document.getElementById('tempBody');
        tbody.innerHTML = '<tr><td colspan="2">⚠️ Не удалось загрузить данные. Проверьте сервер.</td></tr>';
    }
}

setInterval(loadTemperatures, 2500);
loadTemperatures();