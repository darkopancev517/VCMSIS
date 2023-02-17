<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>E-Mail-Verarbeitung | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-email.php" title="15. Kapitel - E-Mail"><link rel="prev" href="base-email-addressing.php" title="15.5. E-Mail-Adressierung"><link rel="next" href="base-email-filter.php" title="15.7. E-Mail-Filter">
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

<a href="base-email-process.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-email-process.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">15.6. E-Mail-Verarbeitung</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-email-addressing.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">15. Kapitel - E-Mail</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-email-filter.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-email-process"></a>15.6. E-Mail-Verarbeitung</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-process-redirect"></a>15.6.1. Weiterleitung</h3></div></div></div><a class="indexterm" name="base-email-process-redirect1"></a><p>Unter Benutzermanager&nbsp;&gt;&nbsp;Benutzer&nbsp;:&nbsp;Weiterleitung k&ouml;nnen Sie die
        benutzerabh&auml;ngige E-Mail-Weiterleitung konfigurieren. Bei der Option
          <span class="guimenuitem">E-Mail-Kopie</span> wird die E-Mail an die eingetragene(n) Adresse(n)
        gesendet und zus&auml;tzlich im Konto des Benutzers gespeichert. Mit der Option
          <span class="guimenuitem">E-Mail-Umleitung</span> wird die E-Mail nur weitergeleitet und nicht
        mehr im Konto des Benutzers gespeichert.</p><p>Soll die E-Mail an mehrere Empf&auml;nger weitergeleitet werden, so geben Sie deren Adressen
        mit Komma getrennt ein.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Verwenden Sie f&uuml;r den Benutzer, der als Postmaster fungiert, nie
            <span class="guimenuitem">E-Mail-Umleitung</span> sondern immer
            <span class="guimenuitem">E-Mail-Kopie</span>. Denn sollte es ein Problem beim E-Mail-Versand
          geben, kann auch der Postmaster keine Mails mehr empfangen. Dabei k&ouml;nnen E-Mails verloren
          gehen. Da lokal keine Fehler-Benachrichtigungen abgerufen werden k&ouml;nnen, wird die
          Fehlersuche unter Umst&auml;nden deutlich erschwert.</p></td></tr></table></div><a class="indexterm" name="d0e4101"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-process-answer"></a>15.6.2. Automatische Antwort</h3></div></div></div><a class="indexterm" name="base-email-process-answer1"></a><p>Unter Benutzermanager&nbsp;&gt;&nbsp;Benutzer&nbsp;:&nbsp;Abwesenheit k&ouml;nnen Sie die
        Automatische Antwort (Abwesenheitsschaltung) aktivieren. Dann wird jede E-Mail automatisch
        mit der eingestellten Antwort beantwortet. Um versehentliche E-Mail-St&uuml;rme usw. zu
        vermeiden, wird an jeden Empf&auml;nger normalerweise nur jeden Tag eine einzige Antwort
        geschickt.</p><p>Um zu vermeiden, dass Mailinglisten oder Spam-E-Mails automatisch beantwortet werden,
        antwortet die Abwesenheitsschaltung nur auf E-Mails, in denen eine diesem Benutzer
        zugewiesene Empf&auml;ngeradresse in den To:- oder Cc:-Kopfzeilen der E-Mail eingetragen
        ist.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Sie m&uuml;ssen daher alle extern erreichbare E-Mail-Adressen und E-Mail-Aliases dieses
          Benutzers im Reiter <span class="guimenu">Adressen</span> eintragen (speziell nat&uuml;rlich die externen
          POP-Konten). Sonst kann die Abwesenheitsschaltung nicht funktionieren.</p></td></tr></table></div><p>Die Automatische Antwort kann zeitgesteuert aktiviert und deaktiviert werden. Tragen Sie
        bei <span class="guimenuitem">von</span> ein Datum ein, wird an diesem Tag zur eingestellten
        Stunde die Automatische Antwort aktiviert. Tragen Sie bei <span class="guimenuitem">bis</span> ein
        Datum ein, wird an diesem Tag zur eingestellten Stunde die Automatische Antwort deaktiviert.
        Sie k&ouml;nnen auch eines der Datumsfelder leer lassen, dann ist die automatische Antwort ab
        sofort bis zum eingestellten Zeitpunkt aktiv bzw. ab dem eingestellen Zeitpunkt aktiv bis
        sie in diesem Men&uuml; wieder abgestellt wird.</p><a class="indexterm" name="d0e4128"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-process-sort"></a>15.6.3. Sortierung</h3></div></div></div><a class="indexterm" name="base-email-process-sort1"></a><p>Unter Benutzermanager&nbsp;&gt;&nbsp;Benutzer&nbsp;:&nbsp;Sortierung k&ouml;nnen
        serverseitige Sortierregeln angelegt werden. Im Vergleich zu Sortierregeln im Clientprogramm
        haben diese den Vorteil, dass sie direkt beim Empfang der E-Mail ausgef&uuml;hrt werden und auch
        ohne laufenden Mailclient zuverl&auml;ssig arbeiten.</p><p>Es k&ouml;nnen beliebig viele Sortierregeln angelegt werden. Bei jeder Regel wird eine Aktion
        (In Unterordner verschieben, weiterleiten, ablehnen, l&ouml;schen) hinterlegt. Wird ein oder alle
        (einstellbar) Sortierkriterium von einer E-Mail erf&uuml;llt, wird die Aktion ausgef&uuml;hrt.</p><p>Als Kriterium f&uuml;r die Sortierung k&ouml;nnen alle Kopfzeilen der E-Mail (z.B. Empf&auml;nger,
        Absender, Betreff) verwendet werden. Es k&ouml;nnen beliebig viele Kriterien f&uuml;r eine Regel
        zusammengefasst werden.</p><a class="indexterm" name="d0e4143"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-email-addressing.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-email.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-email-filter.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">15.5. E-Mail-Adressierung&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;15.7. E-Mail-Filter</td></tr></table></div>
      
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