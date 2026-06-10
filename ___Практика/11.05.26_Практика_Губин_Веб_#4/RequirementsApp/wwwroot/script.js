async function loadRequirements() {
    const search = document.getElementById('search').value;
    const status = document.getElementById('statusFilter').value;
    const resp = await fetch(`/api/requirements?search=${search}&status=${status}`);
    const data = await resp.json();
    const tbody = document.querySelector('#requirementsTable tbody');
    tbody.innerHTML = '';
    data.forEach(r => {
        const row = tbody.insertRow();
        row.innerHTML = `
            <td><a href="detail.html?id=${r.id}">${r.id}</a></td>
            <td>${r.title}</td>
            <td>${r.priority}</td>
            <td>${r.status}</td>
            <td>${r.author?.fullName || ''}</td>
        `;
    });
}
// Загрузка списка при открытии
if (document.getElementById('requirementsTable')) {
    loadRequirements();
}