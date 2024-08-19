function configureInput(element, initialValue, setter) {
    switch (element.type) {
        case 'text':
            element.value = initialValue;
            element.addEventListener('change', () => {
                setter(element.value);
            });
            break;
        case 'checkbox':
            element.checked = initialValue === 'true';
            element.addEventListener('change', () => {
                setter(element.checked ? 'true' : 'false');
            });
            break;
        default:
            console.warn("Unknown input type:", element.type);
            break;
    }
}

function configureSelect(element, initialValue, setter) {
    const selectedElement = element.querySelector(`option[value="${initialValue}"]`);
    if (selectedElement)
        selectedElement.selected = true;

    element.addEventListener("change", () => {
        setter(element.value);
    });
}

document.addEventListener('DOMContentLoaded', () => {
    const elements = document.querySelectorAll('[data-settings-key]');
    for (const element of elements) {
        const key = element.dataset.settingsKey;

        const initialValue = settings.get(key);
        const setter = (value) => settings.set(key, value);

        switch (element.tagName) {
            case 'INPUT':
                configureInput(element, initialValue, setter);
                break;
            case 'SELECT':
                configureSelect(element, initialValue, setter);
                break;
            default:
                console.warn('Unknown element type:', element.tagName);
                break;
        }
    }
});
