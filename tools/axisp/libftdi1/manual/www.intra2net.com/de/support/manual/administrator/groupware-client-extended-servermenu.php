<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Serverseitige Einstellungen in Outlook bearbeiten | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-extended.php" title="22. Kapitel - Erweiterte Funktionen"><link rel="prev" href="groupware-client-extended-folderoptions.php" title="22.4. Ordneroptionen"><link rel="next" href="groupware-client-extended-ol-syncfreq.php" title="22.6. Synchronisationsfrequenz von E-Mails konfigurieren">
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

<a href="groupware-client-extended-servermenu.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-extended-servermenu.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">22.5. Serverseitige Einstellungen in Outlook bearbeiten</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-extended-folderoptions.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">22. Kapitel - Erweiterte Funktionen</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-extended-ol-syncfreq.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-extended-servermenu"></a>22.5. Serverseitige Einstellungen in Outlook bearbeiten</h2></div></div></div><p>Der Intra2net Groupware Client bietet eine einfache M&ouml;glichkeit f&uuml;r die Benutzer, ihre
            serverseitigen Benutzereinstellungen direkt aus der Outlook-Oberfl&auml;che heraus zu
            verwalten.</p><p>Dar&uuml;ber k&ouml;nnen die Funktionen Abwesenheitsschaltung, E-Mail-Weiterleitung,
            Sortierregeln sowie der benutzerabh&auml;ngige Spamfilter des Intranator Servers konfiguriert
            werden.</p><p>Voraussetzung ist nat&uuml;rlich, dass der Administrator des Intranator Servers den
            einzelnen Benutzern die Konfiguration dieser Einstellungen gestattet. Dies kann auf dem
            Server &uuml;ber das Men&uuml;
                <span class="guimenu">Benutzermanager&nbsp;&gt;&nbsp;Gruppen&nbsp;:&nbsp;Administrationsrechte</span>
            z.B. bei der <code class="option">Alle</code>-Gruppe geschehen, in dem die Seiten unterhalb von
                <span class="guimenuitem">Benutzermanager&nbsp;&gt;&nbsp;Eigenes Profil</span> zu den
            erlaubten Seiten hinzugef&uuml;gt werden.</p><p>Die einzelnen Benutzer k&ouml;nnen dann wie folgt die serverseitigen Einstellungen
            anpassen:</p><div class="procedure"><ol type="1"><li><p>Pr&uuml;fen Sie zuerst die Konfiguration des Kontos im Intra2net Groupware Client.
                    &Ouml;ffnen Sie dazu das Men&uuml; <span class="guimenu">Groupware
                        Client&nbsp;&gt;&nbsp;Server-Konten</span>. Kontrollieren Sie, ob die
                    Verschl&uuml;sselung per SSL und die &Uuml;berpr&uuml;fung des Server Zertifikats aktiviert
                    sind. Dies ist die beste M&ouml;glichkeit, eine korrekt gesicherte SSL-Verbindung zum
                    Server sicherzustellen.</p></li><li><p>Sollte es zu SSL- oder Zertifikatsfehlern kommen, m&uuml;ssen Sie die
                    Zertifikatskonfiguration anpassen. Beachten Sie dazu <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-ssl-encryption.php">10. Kapitel,&nbsp;&#8222;SSL-Verschl&uuml;sselung und Zertifikate&#8220;</a>.</p></li><li><p>In der Outlook-Ordnerliste wird ein Ordner <span class="guilabel">Server
                        Einstellungen</span> angezeigt. Darunter finden Sie Ordner f&uuml;r die
                    einzelnen Konten und deren Einstellungen.</p></li><li><p>Klicken Sie die gew&uuml;nschte Maske an und nun k&ouml;nnen Sie direkt innerhalb von
                    Outlook z.B. die Automatische Antwort durch den Server (Abwesenheitsschaltung)
                    konfigurieren. </p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/extended-serverconfig04.png"></div></div><p>
                </p></li></ol></div><p>Die Serverseitigen Einstellungen k&ouml;nnen nur aus Outlook aufgerufen werden, wenn die
            Datendatei des Groupware Clients im Outlook-Profil als Standarddatendatei festgelegt
            ist. Bei nicht als Standard festgelegten Datendateien erscheint zwar der Pfad in der
            Ordnerliste, die dahinterliegenden Seiten k&ouml;nnen aber nicht aufgerufen werden. &Ouml;ffnen
            Sie in diesem Fall die Kontokonfiguration von Outlook und legen die Datendatei des
            Groupware Clients als Standarddatendatei fest.</p></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-extended-folderoptions.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-extended.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-extended-ol-syncfreq.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">22.4. Ordneroptionen&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;22.6. Synchronisationsfrequenz von E-Mails konfigurieren</td></tr></table></div>
      
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