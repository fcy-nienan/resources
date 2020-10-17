> > https://stackoverflow.com/questions/59550222/how-to-show-accept-terms-and-conditions-window-after-click-on-application-exe-fi

```
{
    "appId": "yourappid",
    "productName": "your-product",
    "copyright": "Copyright © 2020 your company",
    "directories": {
      "app": "www"
    },
    "nsis": {
      "oneClick": false,
      "perMachine": false,
      "allowToChangeInstallationDirectory": true,
      "license": "LICENSE.txt", // <- Put your license name here.
    },
    "win": {
      "target": [
        {
          "target": "nsis"
        }
      ]
    }
  }
```

