const MINE_LOG_STORAGE_KEY = 'minesweeperResultsLog';

function loadGameLogs() {
    const raw = localStorage.getItem(MINE_LOG_STORAGE_KEY);
    if (!raw) {
        return [];
    }
    try {
        const parsed = JSON.parse(raw);
        if (Array.isArray(parsed)) {
            return parsed.map((item) => ({
                name: String(item.name || ''),
                steps: Number(item.steps || 0),
                timestamp: item.timestamp || '',
            }));
        }
    } catch (error) {
        console.warn('读取日志失败', error);
    }
    return [];
}

function saveGameLog(name, steps) {
    if (!name || !name.trim()) {
        return;
    }
    const logs = loadGameLogs();
    logs.push({
        name: name.trim(),
        steps: Number(steps) || 0,
        timestamp: new Date().toISOString(),
    });
     const limitedLogs = logs.slice(0, 50);
    localStorage.setItem(MINE_LOG_STORAGE_KEY, JSON.stringify(limitedLogs));
}

function getSortedGameLogs() {
    return loadGameLogs()
        .slice(0,50)
        .sort((a, b) => a.steps - b.steps);
}

function clearGameLogs() {
    localStorage.removeItem(MINE_LOG_STORAGE_KEY);
}
