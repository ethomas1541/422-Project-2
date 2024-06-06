/*
 *	Author: Gus Cochran
 *
 *	Description:
 *		Initialize electron app
 *		
 *	Functions:
 *      createWindow()
 *          creates electron window and preloads "preload.js"
 *	History
 *		6/3/4 initial creation
 *
 * */
const {app, BrowserWindow} = require('electron')
const path = require('path')

const isDev = process.env.NODE_ENV !== 'production'
const onMac = process.platform === 'darwin';

//create browser window instance
function createWindow(){
    const mainWindow = new BrowserWindow({
        title: "Matrix Solver",
        width: isDev ? 1000 : 500,
        height: 500,
        webPreferences: {
            contextIsolation: true,
            nodeIntegration: true,
            preload: path.join(__dirname, 'preload.js'),
        }
    });

    // if(isDev) {
    //     mainWindow.webContents.openDevTools();
    // }

    mainWindow.loadFile(path.join(__dirname, 'index.html'))
    mainWindow.setMenu(null)
}


app.whenReady().then( () => {
    createWindow();
})

app.on('window-all-closed', () => {
    if (!onMac){
        app.quit()
    }
})