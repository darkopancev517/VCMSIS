<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Statistik und Datenschutz | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base.php" title="Teil&nbsp;2.&nbsp;Allgemeine Funktionen"><link rel="prev" href="base-proxy-virus.php" title="12.6. Proxy-Virenscanner"><link rel="next" href="base-statistics-internet.php" title="13.2. Internet-Zugriffsstatistik">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="base-statistics.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-statistics.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">13. Kapitel - Statistik und Datenschutz</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-proxy-virus.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;2.&nbsp;Allgemeine Funktionen</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-statistics-internet.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="base-statistics"></a>13. Kapitel - Statistik und Datenschutz</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="base-statistics.php#base-statistics-proxy">13.1. Proxy-Statistik</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-statistics.php#base-statistics-proxy-logs">13.1.1. Proxy-Protokollierung</a></span></dt><dt><span class="sect2"><a href="base-statistics.php#base-statistics-proxy-analysis">13.1.2. Auswertung</a></span></dt><dt><span class="sect2"><a href="base-statistics.php#base-statistics-proxy-methodology">13.1.3. Methodik</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-statistics-internet.php">13.2. Internet-Zugriffsstatistik</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-statistics-internet.php#base-statistics-internet-methodology">13.2.1. Methodik</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-statistics-storage.php">13.3. Speicherverbrauchsstatistik</a></span></dt><dt><span class="sect1"><a href="base-statistics-dataprivacy.php">13.4. Datenschutz</a></span></dt></dl></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-statistics-proxy"></a>13.1. Proxy-Statistik</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-statistics-proxy-logs"></a>13.1.1. Proxy-Protokollierung</h3></div></div></div><a class="indexterm" name="base-statistics-proxy-logs1"></a><a class="indexterm" name="base-statistics-proxy-logs2"></a><p>Im Men&uuml;
        Information&nbsp;&gt;&nbsp;Statistik&nbsp;&gt;&nbsp;Einstellungen
        wird konfiguriert, ob der im Intranator enthaltene Proxyserver (siehe <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-proxy.php">12. Kapitel,&nbsp;&#8222;Proxy&#8220;</a>) alle Webseitenzugriffe in eine
        Logdatei protokollieren soll oder nicht. Au&szlig;erdem k&ouml;nnen diese Logdateien auch automatisch
        ausgewertet und aufbereitet werden.</p><p>Die Proxy-Logdateien werden, wenn aktiviert, in monatsweise umbrochene Dateien
        geschrieben. Diese sind im Men&uuml;
        Information&nbsp;&gt;&nbsp;System&nbsp;&gt;&nbsp;Logdateien
        abrufbar. Sie werden im Standardformat des Squid-Proxys gespeichert. Dabei wird die Zeit als
        Unix-Zeit in Sekunden seit 1.1.1970 0:00h, UTC angegeben. Wenn Sie die Dateien von Hand
        durchsuchen m&ouml;chten, empfiehlt es sich, die Zeit &uuml;ber die Funktion <span class="guilabel">Herunterladen
          mit normaler Zeit</span> umrechnen zu lassen.</p><a class="indexterm" name="d0e3055"></a><a class="indexterm" name="d0e3056"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-statistics-proxy-analysis"></a>13.1.2. Auswertung</h3></div></div></div><a class="indexterm" name="base-statistics-proxy-analysis1"></a><a class="indexterm" name="base-statistics-proxy-analysis2"></a><p>Wenn aktiviert werden die Proxy-Logdateien auf Monatsbasis ausgewertet und als Statistik
        bereitgestellt. Der aktuelle Monat wird immer zur vollen Stunde aktualisiert. Diese
        Statistik ist unter
        Information&nbsp;&gt;&nbsp;Statistik&nbsp;&gt;&nbsp;Proxy
        abrufbar.</p><p>Die Statistik kann &uuml;ber die Auswahlbox in der oberen Zeile nach Webseiten, Rechnern oder
        Benutzern summiert werden. Eine Darstellung von Benutzerlogins ist nur sinnvoll, wenn der
        Proxy mit Authentifizierung genutzt wird.</p><p>Die Zeilen sind standardm&auml;&szlig;ig nach Zugriffsdauer sortiert, &uuml;ber einen Klick in die
        Kopfzeile k&ouml;nnen sie nach den anderen angezeigten Werten umsortiert werden.</p><p>Die Statistik kann von der &Uuml;bersicht &uuml;ber Webseiten, Rechner und Benutzer weiter auf
        einzelne Rechner, Webseiten oder Tage eingegrenzt werden. Dies wird &uuml;ber einen Klick jeweils
        in die erste dargestellte Spalte erreicht.</p><p>&Uuml;ber das Pfeilsymbol hinter jeder Webseite kann diese direkt im Browser ge&ouml;ffnet und ihr
        Inhalt untersucht werden. Soll eine Seite in Zukunft gesperrt werden, so kann sie mit der
        Checkbox in der letzten Spalte markiert und &uuml;ber den Button unten direkt zu einer
        URL-Sperrliste hinzugef&uuml;gt werden.</p><p>Viele Webseiten laden Ihren Inhalt, sei es nun Text oder Banner-Werbung, von
        unterschiedlichen Servern. Sie werden in Ihrer "Top 50 Webseiten" Auswertung deswegen Server
        wie google-analytics.com, doubleclick.net und weitere finden, welche beim Aufruf auf einer
        Webseite passiv mitgeladen wurden. Diese Inhalte wurde nicht aktiv vom Benutzer
        angesteuert.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-statistics-proxy-methodology"></a>13.1.3. Methodik</h3></div></div></div><p>Im Folgenden wird beschrieben, wie die einzelnen Zugriffe kumuliert und in die
        dargestellten Werte umgewandelt werden.</p><p>Um eine &Uuml;bersicht erst zu erm&ouml;glichen, speichert die Statistik nur einen verk&uuml;rzten
        Namen der aufgerufenen Webadresse. Aus &#8222;http://www.web.de/shopping/&#8220; sowie &#8222;web.de/mail/&#8220;
        wird in beiden F&auml;llen &#8222;web.de&#8220;.</p><p>Die meisten Webseiten bestehen nicht nur aus in HTML formatiertem Text, sondern auch aus
        Grafiken, Flash-Animationen etc. Um eine einigerma&szlig;en aussagef&auml;hige Zahl f&uuml;r die Anzahl der
        aufgerufenen Webseiten zu bekommen, werden f&uuml;r die unter Seitenzugriffe angezeigte Zahl nur
        die Aufrufe gez&auml;hlt, bei denen einer der folgenden Datentypen &uuml;bermittelt wurde: &nbsp; &nbsp;</p><div class="itemizedlist"><ul type="disc"><li><p>text/html</p></li><li><p>text/plain</p></li><li><p>text/javascript</p></li></ul></div><p>
      </p><p>Nach dem Abruf einer Webseite gibt es f&uuml;r den Proxy leider keine M&ouml;glichkeit, genau
        festzustellen, wie lange eine Seite wirklich gelesen wird. Deswegen kann die Proxy-Statistik
        die Dauer nur ann&auml;hernd berechnen.</p><p>F&uuml;r jeden Erstaufruf einer Webseite werden 60 Sekunden Verweildauer angesetzt. Erfolgt
        innerhalb dieser Minute ein weiterer Zugriff auf den gleichen Server, so wird der zeitliche
        Abstand zum letzten Zugriff auf die Dauer addiert. Ist der zeitliche Abstand zwischen zwei
        Zugriffen mehr als 60 Sekunden, so werden die urspr&uuml;nglichen 60 Sekunden erneut angesetzt.
        F&uuml;r die Verweildauer werden nur Abrufe von Datentypen gez&auml;hlt, die auch als Seitenzugriff
        gez&auml;hlt werden (siehe oben).</p><p>Bei Zeitraum&uuml;bersichten wird die Anzahl der Seitenzugriffe einer Stunde zusammengefasst
        und das dargestellte Quadrat wird umso dunkler, je mehr Zugriffe in dieser Stunde
        stattfanden.</p><p>Wird der Zugriff auf eine Webseite durch einen Proxy-Filtermechanismus blockiert, so
        wird der Zugriff weiterhin wie ein normaler Zugriff protokolliert und ausgewertet. Eine
        getrennte Auswertung nach erlaubten und blockierten Zugriffen ist nicht m&ouml;glich.</p><a class="indexterm" name="d0e3110"></a><a class="indexterm" name="d0e3111"></a></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-proxy-virus.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-statistics-internet.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">12.6. Proxy-Virenscanner&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;13.2. Internet-Zugriffsstatistik</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>