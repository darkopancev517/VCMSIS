<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Benutzermanager | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base.php" title="Teil&nbsp;2.&nbsp;Allgemeine Funktionen"><link rel="prev" href="base-statistics-dataprivacy.php" title="13.4. Datenschutz"><link rel="next" href="base-user-manager-user.php" title="14.2. Benutzer">
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

<a href="base-user-manager.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-user-manager.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">14. Kapitel - Benutzermanager</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-statistics-dataprivacy.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;2.&nbsp;Allgemeine Funktionen</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-user-manager-user.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="base-user-manager"></a>14. Kapitel - Benutzermanager</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="base-user-manager.php#base-user-manager-groups">14.1. Benutzergruppen</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-user-manager.php#base-user-manager-groups-rights">14.1.1. Zugriffsrechte</a></span></dt><dt><span class="sect2"><a href="base-user-manager.php#base-user-manager-groups-admin">14.1.2. Administrationsrechte</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-user-manager-user.php">14.2. Benutzer</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-user-manager-user.php#base-user-manager-user-email">14.2.1. Einstellungen f&uuml;r E-Mail und Groupware</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-user-manager-importexport.php">14.3. Import/Export von Benutzerprofilen</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-user-manager-importexport.php#base-user-manager-importexport-import">14.3.1. Import von Benutzern</a></span></dt><dt><span class="sect2"><a href="base-user-manager-importexport.php#base-user-manager-importexport-export">14.3.2. Export von Benutzern</a></span></dt></dl></dd></dl></div><p>&Uuml;ber den Benutzermanager werden alle Benutzer, Benutzereinstellungen (wie z.B.
    E-Mail-Adressen und -Weiterleitungen) sowie alle Zugriffsrechte (u.a. f&uuml;r die Administration,
    Proxy, usw.) verwaltet.</p><p>Beim Benutzer selbst werden nur seine Einstellungen gespeichert, die Zugriffsrechte werden
    ausschlie&szlig;lich &uuml;ber die Benutzergruppen verwaltet.</p><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-user-manager-groups"></a>14.1. Benutzergruppen</h2></div></div></div><a class="indexterm" name="base-user-manager-groups1"></a><p>Jeder Benutzer erh&auml;lt seine Zugriffsrechte von den Benutzergruppen, in denen er Mitglied
      ist. Ein Benutzer kann in beliebig vielen Gruppen Mitglied sein.</p><div class="tip" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Tip"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Tipp]" src="../images/admon/tip.png"></td><th align="left">Tipp</th></tr><tr><td align="left" valign="top"><p>Sie k&ouml;nnen unter
        Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Verteiler eine
        Mailingliste f&uuml;r eine Gruppe anlegen. Dann k&ouml;nnen Sie z.B. mit einer E-Mail an
          <code class="email">&lt;<a class="email" href="mailto:alle@net.lan">alle@net.lan</a>&gt;</code> alle Mitarbeiter erreichen.</p></td></tr></table></div><p>Es gibt 2 spezielle Benutzergruppen: Zum einen die Administratoren-Gruppe. Sie hat alle
      Zugriffsrechte und ist die Einzige, die auf die Konsole zugreifen darf. </p><p>Zum anderen die Alle-Gruppe. Alle Benutzer sind Mitglied in dieser Gruppe. </p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Alle Zugriffsrechte, die die Alle-Gruppe erh&auml;lt, sind ohne Login und Passwort
        zug&auml;nglich. Also kann auch ein Gast ganz ohne Login diese Seiten aufrufen und
        bearbeiten.</p></td></tr></table></div><a class="indexterm" name="d0e3202"></a><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-user-manager-groups-rights"></a>14.1.1. Zugriffsrechte</h3></div></div></div><a class="indexterm" name="base-user-manager-groups-rights1"></a><a class="indexterm" name="base-user-manager-groups-rights2"></a><p>Alle Rechte, die in mindestens einer Gruppe eines Benutzers erlaubt sind, sind f&uuml;r den
        Benutzer erlaubt. </p><p>Bei den Proxy-Profilen werden alle Profile aus den Gruppen eines Benutzers so
        zusammengef&uuml;gt, dass alle Seiten, die in mindestens einer Gruppe erlaubt sind, f&uuml;r den
        Benutzer erlaubt sind. Weitere Informationen zu Proxy-Profilen finden Sie in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-proxy-url.php">Abschnitt&nbsp;12.4, &#8222;URL-Filter&#8220;</a>.</p><p>Ist der E-Mail-Anhangfilter aktiviert, k&ouml;nnen eingehende E-Mails anhand der Gruppe mit
        unterschiedlichen Filterlisten bearbeitet werden. Ist ein Benutzer in mehreren Gruppen mit
        unterschiedlichen Filterlisten Mitglied, so werden die Filterlisten gemischt. Freigabelisten
        haben dabei Vorrang vor Sperrlisten. Weitere Informationen zum E-Mail-Anhangfilter finden
        Sie in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-email-filter.php#base-email-filter-attachment">Abschnitt&nbsp;15.7.3, &#8222;Anhangfilter&#8220;</a>.</p><p>Da alle Benutzer automatisch Mitglied der &#8222;Alle&#8220;-Gruppe sind, sind die Rechte der
        &#8222;Alle&#8220;-Gruppe effektiv die Mindestrechte, die Sie Benutzern vergeben k&ouml;nnen.</p><p>E-Mail-Quota ist der Speicherplatz, welchen die Mailboxen der Mitglieder einer Gruppe
        einzeln maximal belegen d&uuml;rfen (nicht alle Mitglieder gemeinsam). Ist das Limit erreicht,
        werden keine neuen E-Mails mehr angenommen (Fehlermeldung &#8222;450 Over Quota&#8220; geht nach Ablauf
        der E-Mail-Warteschlangenzeit an den Absender). Die meisten IMAP-E-Mail-Clients zeigen ab
        einer Belegung von 90% eine Warnung an. Ist der Benutzer in mehreren Gruppen Mitglied, gilt
        f&uuml;r ihn die gr&ouml;&szlig;te Quota aus seinen Benutzergruppen.</p><a class="indexterm" name="base-user-manager-groups-rights-smtp1"></a><a class="indexterm" name="base-user-manager-groups-rights-smtp2"></a><a class="indexterm" name="base-user-manager-groups-rights-smtp3"></a><p>&Uuml;ber die Option <span class="guimenuitem">SMTP-Authentifizierung und E-Mail-Relaying</span>
        kann man steuern, ob sich die Mitglieder der Gruppe zum Versand von E-Mails an externe
        Empf&auml;nger am Intranator anmelden k&ouml;nnen (SMTP-Authentifizierung). Beachten Sie, dass die
        Mitglieder einer Gruppe mit E-Mail-Relaying aus dem Internet unbedingt Passw&ouml;rter hoher
        Qualit&auml;t ben&ouml;tigen. Ansonsten kann das Passwort automatisiert erraten und der Intranator zum
        Versand von Spam missbraucht werden.</p><a class="indexterm" name="d0e3254"></a><a class="indexterm" name="d0e3255"></a><a class="indexterm" name="d0e3256"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-user-manager-groups-admin"></a>14.1.2. Administrationsrechte</h3></div></div></div><p>Unter
        Benutzermanager&nbsp;&gt;&nbsp;Gruppen&nbsp;:&nbsp;Administrationsrechte
        k&ouml;nnen Sie im unteren Bildschirmteil den Zugriff auf jede einzelne Seite der Oberfl&auml;che
        reglementieren. Im oberen Teil l&auml;sst sich einstellen, ob die unten eingestellten Rechte auch
        &uuml;ber das Internet genutzt werden k&ouml;nnen sollen (Fernadministration), oder ob nur Zugriff auf
        Web-Groupware m&ouml;glich sein soll.</p><p>Au&szlig;erdem l&auml;sst sich einstellen, ob das Aufbauen und Trennen von Internet- und VPN-
        Verbindungen gestattet ist oder nicht.</p><p>Wenn Sie m&ouml;chten, dass ohne Login die Hauptseite verborgen sein soll, m&uuml;ssen Sie einfach
        der Alle-Gruppe das Zugriffsrecht &#8222;Hauptseite&#8220; entziehen.</p><a class="indexterm" name="d0e3266"></a><a class="indexterm" name="d0e3267"></a></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-statistics-dataprivacy.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-user-manager-user.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">13.4. Datenschutz&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;14.2. Benutzer</td></tr></table></div>
      
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